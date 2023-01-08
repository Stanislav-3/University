from PyQt5.QtWidgets import QGraphicsRectItem, QGraphicsTextItem, QGraphicsItem
from place import Place
import threading
from PyQt5.QtCore import QTimer

class Transition(QGraphicsRectItem):
    _count = 0

    @classmethod
    def drop_count(cls):
        cls._count = 0

    @classmethod
    def decrement_count(cls):
        cls._count -= 1

    def __init__(self, width, height, brush, pen):
        super(Transition, self).__init__(0, 0, width, height)
        Transition._count += 1

        self.id = Transition._count
        self.vertical = True
        self.width = width
        self.height = height

        self.edges_in = set()
        self.edges_out = set()

        self.setFlag(QGraphicsItem.ItemIsMovable)
        self.setFlag(QGraphicsItem.ItemIsSelectable)
        self.setFlag(QGraphicsItem.ItemSendsGeometryChanges)

        self.text = QGraphicsTextItem(f'T{self.id}', self)
        self.text.setPos((width - self.text.boundingRect().width()) / 2, height)

        self.setBrush(brush)
        self.setPen(pen)

    def __del__(self, scene):
        for edge in self.edges_out | self.edges_in:
            edge.__del__(scene, False)

        scene.removeItem(self)

    def decrement_id(self):
        self.id -= 1
        self.text.setPlainText(f'P{self.id}')

    def change_orientation(self):
        self.vertical = not self.vertical

        if self.vertical:
            self.setRect(0, 0, self.width, self.height)
            self.text.setPos((self.width - self.text.boundingRect().width()) / 2, self.height)
        else:
            self.setRect(0, 0, self.height, self.width)
            self.text.setPos((self.height - self.text.boundingRect().width()) / 2, self.width)

        for edge in self.edges_in | self.edges_out:
            edge.adjust()

    def add_edge(self, edge, edge_type='in'):
        if edge_type == 'in':
            self.edges_in.add(edge)
        elif edge_type == 'out':
            self.edges_out.add(edge)
        else:
            raise ValueError('Unknown edge type')

    def remove_edge(self, edge):
        if edge in self.edges_out:
            self.edges_out.remove(edge)
        elif edge in self.edges_in:
            self.edges_in.remove(edge)

    def itemChange(self, change, value):
        if change == QGraphicsItem.ItemPositionHasChanged:
            for edge in self.edges_in | self.edges_out:
                edge.adjust()

        return QGraphicsItem.itemChange(self, change, value)

    def get_local_center(self, x, y, shift=False):
        delta = 0
        if shift:
            if len(self.edges_in) > 0:
                e = self.edges_in.pop()
                self.edges_in.add(e)

                delta = e.source.mark_diameter / 2
            elif len(self.edges_out) > 0:
                e = self.edges_out.pop()
                self.edges_out.add(e)

                delta = e.target.mark_diameter / 2
            else:
                delta = 0

        if self.vertical:
            return x + self.width / 2 - delta, y + self.height / 2 - delta
        else:
            return x + self.height / 2 - delta, y + self.width / 2 - delta

    def decrement_sources_marks(self):
        for edge in self.edges_in:
            if type(edge.source) is Place:
                edge.source.update_marks(-1)

    def increment_target_marks(self):
        for edge in self.edges_out:
            if type(edge.target) is Place:
                edge.target.update_marks(+1)

    def transit(self, delay, parent):
        delay = delay / 2

        for edge in self.edges_in:
            edge.transit(delay)

        def transit_out():
            for edge in self.edges_out:
                edge.transit(delay)

        timer = QTimer(parent)
        timer.timeout.connect(transit_out)
        timer.setSingleShot(True)
        timer.start(delay * 1000)

    def can_transit(self):
        if len(self.edges_in) == 0 or len(self.edges_out) == 0:
            return False

        for edge in self.edges_in:
            if edge.source.mark_count == 0:
                return False

        return True
