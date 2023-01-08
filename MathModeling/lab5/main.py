from PyQt5 import QtGui, QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QBrush, QPen, QTransform
from PyQt5.QtCore import Qt, QPointF
from place import Place
from transition import Transition
from edge import Edge
import sys
from petri_net import PetriNetQThread, try_to_transit
from marking_diagram import MarkingDiagram
import pickle


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.widget = QWidget()

        self.title = "Petri nets"

        self.top = 150
        self.left = 150
        self.width = 1200
        self.height = 500

        self.view_top = 50

        self.buttons_width = 100
        self.buttons_height = 30

        petri_net.parent = self

        self.InitUi()

    def InitUi(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.top, self.left, self.width, self.height)

        self.createInterfacePanel()
        self.createGraphicView()

        self.show()

    def createInterfacePanel(self):
        self.place_button = QPushButton('Place', self)
        self.transition_button = QPushButton('Transition', self)
        self.remove_button = QPushButton('Remove', self)
        self.clear_button = QPushButton('Clear', self)

        self.add_mark_button = QPushButton('+', self)
        self.remove_mark_button = QPushButton('-', self)

        self.change_orientation_button = QPushButton('↺', self)

        self.run_button = QPushButton('Run', self)
        self.stop_button = QPushButton('Stop', self)

        self.tree_diagram = QTreeWidget(self)

        # self.task_comboBox = QComboBox(self)
        # self.save_button = QPushButton('Save', self)

        y = int((self.view_top - self.buttons_height) / 2)

        self.place_button.setGeometry(10, y, self.buttons_width, self.buttons_height)
        self.transition_button.setGeometry(10 + 1 * self.buttons_width, y, self.buttons_width, self.buttons_height)
        self.remove_button.setGeometry(10 + 2 * self.buttons_width, y, self.buttons_width, self.buttons_height)
        self.clear_button.setGeometry(10 + 3 * self.buttons_width, y, self.buttons_width, self.buttons_height)

        self.add_mark_button.setGeometry(int(10 + 4.5 * self.buttons_width), y, self.buttons_width, self.buttons_height)
        self.remove_mark_button.setGeometry(int(10 + 5.5 * self.buttons_width), y, self.buttons_width, self.buttons_height)
        self.change_orientation_button.setGeometry(int(10 + 6.5 * self.buttons_width), y, self.buttons_width, self.buttons_height)

        self.run_button.setGeometry(int(10 + 8 * self.buttons_width), y, self.buttons_width,
                                                   self.buttons_height)
        self.stop_button.setGeometry(int(10 + 9 * self.buttons_width), y, self.buttons_width,
                                                   self.buttons_height)

        self.tree_diagram.setGeometry(int(10 + 10 * self.buttons_width), y, 180, 40)
        self.tree_diagram.setHeaderHidden(True)

        # self.task_comboBox.setGeometry(int(10 + 10 * self.buttons_width), y, self.buttons_width,
        #                              self.buttons_height)
        # self.save_button.setGeometry(int(10 + 11 * self.buttons_width), y, self.buttons_width,
        #                                self.buttons_height)

        # self.task_comboBox.addItem('empty')
        # self.task_comboBox.addItem('task 1')
        # self.task_comboBox.addItem('task 2')
        # self.task_comboBox.setCurrentIndex(1)

        self.place_button.clicked.connect(self.createPlace)
        self.transition_button.clicked.connect(self.createTransition)
        self.remove_button.clicked.connect(self.removeElement)
        self.clear_button.clicked.connect(self.removeAll)

        self.add_mark_button.clicked.connect(lambda: self.scene.updateMarks(1))
        self.remove_mark_button.clicked.connect(lambda: self.scene.updateMarks(-1))

        self.change_orientation_button.clicked.connect(lambda: self.scene.change_orientation())

        self.run_button.clicked.connect(petri_net.start)
        self.stop_button.clicked.connect(petri_net.stop)
        self.run_button.clicked.connect(lambda: self.scene.set_active(False))
        self.run_button.clicked.connect(lambda: self.generate_marking_diagram())
        self.stop_button.clicked.connect(lambda: self.scene.set_active(True))

        petri_net.transitSignal.connect(lambda: try_to_transit(transitions, parent=self))

        # self.task_comboBox.activated.connect(self.load_scene)
        # self.save_button.clicked.connect(self.save_scene)

    # def save_scene(self):
    #     idx = self.task_comboBox.currentIndex()
    #     name = ''
    #
    #     if idx == 0:
    #         return
    #     elif idx == 1:
    #         name = 'task_1'
    #     elif idx == 2:
    #         name = 'task_2'
    #
    #     with open(name + '_places' + '.pkl', 'wb') as fp:
    #         objects = []
    #         for place in places:
    #             objects.append({
    #                 'mark_count': place.mark_count,
    #
    #             })
    #
    #         pickle.dump(places, fp)
    #
    # def load_scene(self):
    #     idx = self.task_comboBox.currentIndex()
    #     name = ''
    #
    #     if idx == 0:
    #         self.removeAll()
    #     elif idx == 1:
    #         name = 'task_1'
    #     elif idx == 2:
    #         name = 'task_2'
    #
    #     global places
    #     with open(name + '_places' + '.pkl', 'rb') as fp:
    #         places = pickle.load(fp)
    #
    #     for place in places:
    #         self.scene.addItem(place)

    def createGraphicView(self):
        self.view_width = self.width - 20

        self.scene = Scene()

        graphicView = QGraphicsView(self.scene, self)
        graphicView.setMouseTracking(True)
        graphicView.setGeometry(10, self.view_top, self.view_width, self.height - self.view_top - 10)
        self.scene.setSceneRect(0, 0, self.view_width - 10, self.height - self.view_top - 20)

    def createPlace(self):
        place = self.scene.add_place()
        places.add(place)

    def createTransition(self):
        transition = self.scene.add_transition()
        transitions.add(transition)

    def removeElement(self):
        element = self.scene.get_selected_element()
        element.__del__(self.scene)

        # Delete item & update id's
        if type(element) is Place:
            for place in places:
                if place.id > element.id:
                    place.decrement_id()

            element.decrement_count()
            places.remove(element)
        elif type(element) is Transition:
            for transition in transitions:
                if transition.id > element.id:
                    transition.decrement_id()

            element.decrement_count()
            transitions.remove(element)
        elif type(element) is Edge:
            element.__del__(self.scene)

    def removeAll(self):
        self.scene.clear()

        Place.drop_count()
        Transition.drop_count()

        places.clear()
        transitions.clear()

        petri_net.stop()

    def generate_marking_diagram(self):
        MarkingDiagram(self.tree_diagram, places=places, transitions=transitions)


class Scene(QGraphicsScene):
    def __init__(self):
        super().__init__()
        self.grayBrush = QBrush(Qt.gray)
        self.pen = QPen(Qt.black)
        self.mark_brush = QBrush(Qt.black)

        self.circle_diameter = 50
        self.transaction_width = 10
        self.transaction_height = 70

        self.cmd_is_pressed = False
        self.moving_edge = None
        self.mouse_QPointF = None

    def get_selected_element(self):
        selected_items = self.selectedItems()
        if len(selected_items) == 0:
            return None

        return selected_items[0]

    def set_active(self, active=True):
        for item in self.items():
            item.setFlag(QGraphicsItem.ItemIsMovable, active)
            item.setFlag(QGraphicsItem.ItemIsSelectable, active)

    def updateMarks(self, delta):
        selected_element = self.get_selected_element()
        if selected_element is None or type(selected_element) is not Place:
            return

        selected_element.update_marks(delta)

    def add_place(self):
        place = Place(self.circle_diameter, self.grayBrush, self.pen, self.mark_brush)
        self.addItem(place)

        return place

    def add_transition(self):
        transaction = Transition(self.transaction_width, self.transaction_height, self.grayBrush, self.pen)
        self.addItem(transaction)

        return transaction

    def change_orientation(self):
        selected_element = self.get_selected_element()
        if selected_element is None or type(selected_element) is not Transition:
            return

        selected_element.change_orientation()

    def keyPressEvent(self, event):
        super(Scene, self).keyPressEvent(event)
        if event.key() == QtCore.Qt.Key_Control:
            self.cmd_is_pressed = True

    def keyReleaseEvent(self, event):
        super(Scene, self).keyReleaseEvent(event)
        if event.key() == QtCore.Qt.Key_Control:
            self.cmd_is_pressed = False

            if self.moving_edge is None:
                return

            items = self.items(self.mouse_QPointF)
            if len(items) < 3:
                self.removeItem(self.moving_edge)
                self.moving_edge = None
                return

            item = items[2]
            # if type(item) is not Place and type(item) is not Transition:
            #     self.removeItem(self.moving_edge)
            #     self.moving_edge = None
            #
            # self.moving_edge.set_target(item)
            # self.moving_edge = None

            if type(item) is Place and type(self.moving_edge.source) is Transition\
                    or type(item) is Transition and type(self.moving_edge.source) is Place:
                self.moving_edge.set_target(item)
            else:
                self.removeItem(self.moving_edge)

            self.moving_edge = None

    def mouseMoveEvent(self, event: QtGui.QMouseEvent) -> None:
        super(Scene, self).mouseMoveEvent(event)

        element = self.get_selected_element()
        if element is None or type(element) is Edge:
            return

        if self.cmd_is_pressed:
            if self.moving_edge is None:
                self.moving_edge = Edge(element, event, self)
                self.addItem(self.moving_edge)
            else:
                self.moving_edge.adjust()

        self.mouse_QPointF = event.scenePos()


places = set()
transitions = set()
petri_net = PetriNetQThread()

App = QApplication(sys.argv)
window = Window()
sys.exit(App.exec())
