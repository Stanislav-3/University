from PyQt5.QtCore import QLineF, Qt, QPointF, QPropertyAnimation, QRectF, QEasingCurve, QEvent, QAbstractAnimation, \
    QObject, pyqtProperty
from PyQt5.QtGui import QPen, QPolygonF, QBrush, QPixmap
from PyQt5.QtWidgets import QGraphicsPathItem, QGraphicsItem, QGraphicsLineItem, QGraphicsPolygonItem, \
    QGraphicsEllipseItem, QGraphicsObject, QGraphicsPixmapItem
from place import Place
from transition import Transition
import numpy as np
from copy import deepcopy


def shift_arrow_point(source, target, dx, dim):
    if source[dim] < target[dim]:
        y = target[dim] - dx
    else:
        y = target[dim] + dx

    return y


def get_connection_point(center1, center2, item):
    if type(item) is Place:
        k = (item.circle_diameter / 2) / np.sqrt((center1[0] - center2[0]) ** 2 + (center1[1] - center2[1]) ** 2)

        dx = k * np.abs(center1[0] - center2[0])
        dy = k * np.abs(center1[1] - center2[1])

        if center2[0] > center1[0]:
            x = center1[0] + dx
        else:
            x = center1[0] - dx

        if center2[1] > center1[1]:
            y = center1[1] + dy
        else:
            y = center1[1] - dy

        return x, y
    elif type(item) is Transition:
        return center1


class Edge(QGraphicsLineItem):
    def __str__(self):
        if type(self.target) is Place or type(self.target) is Transition:
            return f'E {self.source.id} -> {self.target.id}'
        else:
            return f'E {self.source.id} -> mouse'

    def __init__(self, source, target, scene=None, parent=None):
        super(Edge, self).__init__(parent)
        self.setFlag(QGraphicsItem.ItemIsSelectable)
        self.is_transitioning = False

        self.source = source
        self.target = target

        self.source.add_edge(self, 'out')
        self.scene = scene

        if type(self.target) is Place or type(self.target) is Transition:
            self.target.add_edge(self, 'in')
            self.target_is_mouse = False
        else:
            self.target_is_mouse = True

        self.color = Qt.black
        self.color = Qt.white
        self.pen = QPen(self.color)
        self.brush = QBrush(self.color)

        # Line
        self.setPen(self.pen)

        # Arrow
        self.arrow = QGraphicsPolygonItem(self)
        self.arrow.setPen(self.pen)
        self.arrow.setBrush(self.brush)
        self.arrow_len = 15
        self.arrow_width = 10

        self.adjust()

    def __del__(self, scene, delete_source_edge=True):
        print('Delete in edge', self)
        scene.removeItem(self)

        if delete_source_edge:
            self.source.remove_edge(self)

        if type(self.target) is Place or type(self.target) is Transition:
            self.target.remove_edge(self)

    def adjust(self):
        self.prepareGeometryChange()

        pos_source = self.source.pos()
        pos_target = self.target.scenePos()

        center_source = self.source.get_local_center(pos_source.x(), pos_source.y())

        if self.target_is_mouse:
            target_connection_point = center_target = (pos_target.x(), pos_target.y())
            source_connection_point = get_connection_point(center_source, center_target, self.source)
            source = QPointF(*source_connection_point)
            target = pos_target
        else:
            center_target = self.target.get_local_center(pos_target.x(), pos_target.y())
            source_connection_point = get_connection_point(center_source, center_target, self.source)
            target_connection_point = get_connection_point(center_target, center_source, self.target)

            source = QPointF(*source_connection_point)
            target = QPointF(*target_connection_point)

        # Line
        self.setLine(QLineF(source, target))

        # Arrow
        s = np.sqrt((center_source[0] - center_target[0]) ** 2 + (center_source[1] - center_target[1]) ** 2)
        alpha = np.arcsin(np.abs((center_source[0] - center_target[0]) / s))
        beta = np.arctan(0.5 * self.arrow_width / self.arrow_len)
        gamma = alpha - beta
        arrow_edge_len = np.sqrt((0.5 * self.arrow_width) ** 2 + self.arrow_len ** 2)

        dx = arrow_edge_len * np.sin(gamma)
        dy = arrow_edge_len * np.cos(gamma)
        dx2 = arrow_edge_len * np.sin(beta + alpha)
        dy2 = arrow_edge_len * np.cos(beta + alpha)

        self.arrow.setPolygon(
            QPolygonF([
                QPointF(target_connection_point[0], target_connection_point[1]),
                QPointF(shift_arrow_point(source_connection_point, target_connection_point, dx, 0),
                        shift_arrow_point(source_connection_point, target_connection_point, dy, 1)),
                QPointF(shift_arrow_point(source_connection_point, target_connection_point, dx2, 0),
                        shift_arrow_point(source_connection_point, target_connection_point, dy2, 1)),
                QPointF(target_connection_point[0], target_connection_point[1]),
            ])
        )

    def set_target(self, target):
        self.target = target

        if type(self.target) is Place or type(self.target) is Transition:
            self.target.add_edge(self, 'in')
            self.target_is_mouse = False
        else:
            self.target_is_mouse = True

        self.adjust()

    def transit(self, delay):
        if self.is_transitioning:
            return
        self.set_transitioning(True)

        if type(self.source) is Place:
            d = self.source.mark_diameter
        else:
            d = self.target.mark_diameter

        s, t = self.source.scenePos(), self.target.scenePos()
        s_center = self.source.get_local_center(s.x(), s.y(), shift=True)
        t_center = self.target.get_local_center(t.x(), t.y(), shift=True)

        ball = CustomEllipse(d, self.color, self)

        self.animation = Animation(ball, self.scene)
        self.animation.setDuration(delay * 1000)

        self.animation.setStartValue(QPointF(*s_center))
        self.animation.setEndValue(QPointF(*t_center))

        self.animation.setLoopCount(1)
        self.animation.start(QPropertyAnimation.DeleteWhenStopped)
        self.animation.finished.connect(lambda: self.scene.removeItem(ball))
        self.animation.finished.connect(lambda: self.set_transitioning(False))
        # self.scene.addItem(ball)

    def set_transitioning(self, state):
        self.is_transitioning = state


class Animation(QPropertyAnimation):
    def __init__(self, obj, scene=None):
        self.obj = obj
        self.scene = scene

        super(Animation, self).__init__(self.obj, b'pos')

    # def event(self, event: QEvent) -> bool:
    #     return super(Animation, self).event(event)

    # def updateState(self, newState: QAbstractAnimation.State, oldState: QAbstractAnimation.State) -> None:
    #     super(Animation, self).updateState(newState, oldState)
    #
    #     if newState == QPropertyAnimation.Stopped:
    #         self.obj.setParent(None)
    #         self.scene.removeItem(self.obj)


class CustomEllipse(QGraphicsObject):
    def __init__(self, diameter, color, parent=None):
        QGraphicsObject.__init__(self, parent=parent)

        self.diameter = diameter
        self.color = color

    def boundingRect(self):
        return QRectF(0, 0, self.diameter, self.diameter)

    def paint(self, painter, styles, widget=None):
        painter.setPen(QPen(self.color))
        painter.setBrush(QBrush(self.color))
        painter.drawEllipse(self.boundingRect())


# class Ball(QObject):
#     def __init__(self, parent=None):
#         super().__init__(parent=parent)
#         self.pixmap_item = QGraphicsPixmapItem(QPixmap('ball.png'))
#
#     def _set_pos(self, pos):
#         self.pixmap_item.setPos(pos)
#
#     pos = pyqtProperty(QPointF, fset=_set_pos)