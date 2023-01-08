from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QGraphicsEllipseItem, QGraphicsTextItem, QGraphicsItem


class Place(QGraphicsEllipseItem):
    _count = 0

    @classmethod
    def drop_count(cls):
        cls._count = 0

    @classmethod
    def decrement_count(cls):
        cls._count -= 1

    def __str__(self):
        return f'P{self.id}'

    def __init__(self, diameter, circle_brush, pen, mark_brush):
        super(Place, self).__init__(0, 0, diameter, diameter)
        Place._count += 1

        self.mark_count = 0
        self.id = Place._count
        self.mark_diameter = 0.2 * diameter
        self.edges_in = set()
        self.edges_out = set()

        self.setFlag(QGraphicsItem.ItemIsMovable)
        self.setFlag(QGraphicsItem.ItemIsSelectable)
        self.setFlag(QGraphicsItem.ItemSendsGeometryChanges)

        self.text = QGraphicsTextItem(f'P{self.id}', self)
        self.text.setPos((diameter - self.text.boundingRect().width()) / 2, diameter)

        self.setBrush(circle_brush)
        self.setPen(pen)
        self.circle_diameter = diameter
        self.mark_brush = mark_brush

    def __del__(self, scene):
        print('Edges count', len(self.edges_in | self.edges_out))
        print('Delete in Place', self)

        for edge in self.edges_out | self.edges_in:
            print('Edge', edge)
            edge.__del__(scene, False)

        scene.removeItem(self)

    def decrement_id(self):
        self.id -= 1
        self.text.setPlainText(f'P{self.id}')

    def update_marks(self, delta):
        self.mark_count += delta
        if self.mark_count < 0:
            self.mark_count = 0

        marks = []

        for mark in self.childItems():
            if type(mark) is not QGraphicsEllipseItem:
                continue
            mark.setParentItem(None)

        if self.mark_count == 1:
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter / 2,
                                              self.circle_diameter / 2 - self.mark_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
        elif self.mark_count == 2:
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter,
                                              self.circle_diameter / 2 - self.mark_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2,
                                              self.circle_diameter / 2 - self.mark_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
        elif self.mark_count == 3:
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter,
                                              self.circle_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2,
                                              self.circle_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter / 2,
                                              self.circle_diameter / 2 - self.mark_diameter,
                                              self.mark_diameter, self.mark_diameter, self))
        elif self.mark_count == 4:
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter,
                                              self.circle_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2,
                                              self.circle_diameter / 2,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2 - self.mark_diameter,
                                              self.circle_diameter / 2 - self.mark_diameter,
                                              self.mark_diameter, self.mark_diameter, self))
            marks.append(QGraphicsEllipseItem(self.circle_diameter / 2,
                                              self.circle_diameter / 2 - self.mark_diameter,
                                              self.mark_diameter, self.mark_diameter, self))
        elif self.mark_count > 4:
            d = 0.5 * self.circle_diameter
            mark = QGraphicsEllipseItem(self.circle_diameter / 2 - d / 2,
                                        self.circle_diameter / 2 - d / 2,
                                        d, d, self)
            marks.append(mark)

            text = QGraphicsTextItem(f'{self.mark_count}', mark)
            text.setPos((self.circle_diameter - text.boundingRect().width()) / 2,
                        (self.circle_diameter - text.boundingRect().height()) / 2)
            text.setDefaultTextColor(Qt.white)

        for mark in marks:
            mark.setBrush(self.mark_brush)

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
        # if change == QGraphicsItem.ItemSelectedChange:
        #     self.setBrush(Qt.green if value else Qt.darkGray)

        if change == QGraphicsItem.ItemPositionHasChanged:
            for edge in self.edges_in | self.edges_out:
                edge.adjust()

        return QGraphicsItem.itemChange(self, change, value)

    def get_local_center(self, x, y, shift=False):
        delta = self.circle_diameter / 2

        if shift:
            delta -= self.mark_diameter / 2

        return x + delta, y + delta
