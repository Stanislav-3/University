from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QMainWindow
from users.admin import Admin
from units.order.order_status import Order_status
from units.order.order import Order


class ShowWindow(QMainWindow):
    def __init__(self, my_app, signal):
        self.my_app = my_app
        self.user = None
        self.info = None
        self.current_item_index = None
        self.update_signal = signal

    def setupUi(self, ShowWindow):
        self.sw = ShowWindow
        ShowWindow.setObjectName("ShowWindow")
        ShowWindow.resize(431, 283)
        self.centralwidget = QtWidgets.QWidget(ShowWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.returnButton = QtWidgets.QPushButton(self.centralwidget)
        self.returnButton.setGeometry(QtCore.QRect(0, 230, 71, 32))
        self.returnButton.setObjectName("returnButton")
        self.showItemLabel = QtWidgets.QLabel(self.centralwidget)
        self.showItemLabel.setGeometry(QtCore.QRect(10, 10, 291, 20))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setWeight(75)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.showItemLabel.setFont(font)
        self.showItemLabel.setObjectName("showItemLabel")
        self.showListWidget = QtWidgets.QListWidget(self.centralwidget)
        self.showListWidget.setGeometry(QtCore.QRect(10, 30, 411, 191))
        self.showListWidget.setObjectName("showListWidget")
        self.plusButton = QtWidgets.QPushButton(self.centralwidget)
        self.plusButton.setGeometry(QtCore.QRect(370, 230, 51, 32))
        self.plusButton.setObjectName("plusButton")
        self.minusButton = QtWidgets.QPushButton(self.centralwidget)
        self.minusButton.setGeometry(QtCore.QRect(330, 230, 51, 32))
        self.minusButton.setObjectName("minusButton")
        self.statusComboBox = QtWidgets.QComboBox(self.centralwidget)
        self.statusComboBox.setGeometry(QtCore.QRect(220, 230, 104, 31))
        self.statusComboBox.setObjectName("statusComboBox")
        self.statusComboBox.addItem("")
        self.statusComboBox.addItem("")
        self.statusComboBox.addItem("")
        self.statusComboBox.addItem("")
        self.statusComboBox.addItem("")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(160, 235, 60, 21))
        self.label.setObjectName("label")
        ShowWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(ShowWindow)
        self.statusbar.setObjectName("statusbar")
        ShowWindow.setStatusBar(self.statusbar)

        self.retranslateUi(ShowWindow)
        QtCore.QMetaObject.connectSlotsByName(ShowWindow)

        self.returnButton.clicked.connect(lambda: self.my_app.view_user_window())
        self.showListWidget.itemClicked.connect(lambda: self.list_widget_item_clicked())
        self.plusButton.clicked.connect(lambda: self.plus_button_clicked())
        self.minusButton.clicked.connect(lambda: self.minus_button_clicked())
        self.statusComboBox.currentIndexChanged.connect(lambda: self.validate_orders())

    def retranslateUi(self, ShowWindow):
        _translate = QtCore.QCoreApplication.translate
        ShowWindow.setWindowTitle(_translate("ShowWindow", "MainWindow"))
        self.returnButton.setText(_translate("ShowWindow", "Return"))
        self.showItemLabel.setText(_translate("ShowWindow", "label"))
        self.plusButton.setText(_translate("ShowWindow", "+"))
        self.minusButton.setText(_translate("ShowWindow", "-"))
        self.statusComboBox.setItemText(0, _translate("ShowWindow", "All"))
        self.statusComboBox.setItemText(1, _translate("ShowWindow", "Reserved"))
        self.statusComboBox.setItemText(2, _translate("ShowWindow", "Executing"))
        self.statusComboBox.setItemText(3, _translate("ShowWindow", "Completed"))
        self.statusComboBox.setItemText(4, _translate("ShowWindow", "Canceled"))
        self.label.setText(_translate("ShowWindow", "Status ➔ "))

    def initialize(self, item: str, user, info: list):
        _translate = QtCore.QCoreApplication.translate
        self.showItemLabel.setText(_translate("ShowWindow", item.capitalize() + ':'))
        self.statusComboBox.hide()
        self.label.hide()

        if not isinstance(user, Admin):
            self.minusButton.hide()
            self.plusButton.hide()
        else:
            self.minusButton.show()
            self.plusButton.show()

        self.user = user
        self.info = info
        text = None
        item = item.lower()
        if item == "drivers":
            self.sw.resize(420, 283)
            self.showListWidget.setGeometry(QtCore.QRect(10, 30, 400, 191))
            self.plusButton.setGeometry(QtCore.QRect(365, 230, 51, 32))
            self.minusButton.setGeometry(QtCore.QRect(325, 230, 51, 32))
            text = user.get_drivers(info)
        elif item == "cars":
            self.sw.resize(500, 283)
            self.showListWidget.setGeometry(QtCore.QRect(10, 30, 480, 191))
            self.plusButton.setGeometry(QtCore.QRect(445, 230, 51, 32))
            self.minusButton.setGeometry(QtCore.QRect(405, 230, 51, 32))
            text = user.get_cars(info)
        elif item == "budget":
            self.sw.resize(420, 283)
            self.showListWidget.setGeometry(QtCore.QRect(10, 30, 400, 191))
            self.plusButton.setGeometry(QtCore.QRect(365, 230, 51, 32))
            self.minusButton.setGeometry(QtCore.QRect(325, 230, 51, 32))
            text = user.get_budget(info)
        elif item == "orders":
            self.sw.resize(570, 283)
            self.showListWidget.setGeometry(QtCore.QRect(10, 30, 555, 191))
            self.plusButton.setGeometry(QtCore.QRect(520, 230, 51, 32))
            self.minusButton.setGeometry(QtCore.QRect(480, 230, 51, 32))
            self.statusComboBox.setGeometry(QtCore.QRect(350, 230, 110, 31))
            self.label.setGeometry(QtCore.QRect(290, 235, 60, 21))
            text = user.get_orders(info)
            self.statusComboBox.show()
            self.label.show()
        elif item == "map":
            self.sw.resize(500, 283)
            self.showListWidget.setGeometry(QtCore.QRect(10, 30, 480, 191))
            self.plusButton.setGeometry(QtCore.QRect(445, 230, 51, 32))
            self.minusButton.setGeometry(QtCore.QRect(405, 230, 51, 32))
            text = user.get_map(info)

        self.clear_list_widget()
        self.add_to_list_widget(text[0], text[1])

    def clear_list_widget(self):
        self.showListWidget.clear()

    def make_item_1_a_tittle(self):
        item = self.showListWidget.item(0)
        if item is None:
            return
        # item.setFont(QFont(QFont.Bold))

    def add_to_list_widget(self, title: str, text: list, additional = ''):
        self.clear_list_widget()
        if text is None or len(text) == 0:
            label_text = self.showItemLabel.text()[:-1].lower()
            if label_text.find(' ') >= 0:
                label_text = label_text[:label_text.find(' ')]
            text = ["There's no any " + additional + ' ' + label_text + " in the data base..."]
        else:
            self.showListWidget.addItem(QtWidgets.QListWidgetItem(title))

        for i in range(len(text)):
            self.showListWidget.addItem(QtWidgets.QListWidgetItem(text[i]))

        self.make_item_1_a_tittle()

    def list_widget_item_clicked(self):
        ind = self.showListWidget.currentRow() - 1
        self.current_item_index = ind

    def get_item_name(self):
        text = self.showItemLabel.text()
        text = text[:text.index(':')]
        try:
            text = text[:text.index(' ')]
        except:
            pass
        if text.endswith('s'):
            text = text[:-1]

        return text.lower()

    def plus_button_clicked(self):
        text = self.get_item_name()

        self.my_app.view_input_window(text)

    def minus_button_clicked(self):
        if self.current_item_index is None or self.current_item_index < 0:
            return

        item_name = self.get_item_name()
        self.showListWidget.update()
        attributes_list = self.showListWidget.item(self.current_item_index + 1).text().split('\t')
        item_content = ' '.join(attributes_list)

        msg = QtWidgets.QMessageBox()
        msg.setIcon(QtWidgets.QMessageBox.Question)
        yes_button = msg.addButton(QtWidgets.QMessageBox.Yes)
        no_button = msg.addButton(QtWidgets.QMessageBox.No)
        msg.setWindowTitle("Delete...")
        msg.setText("Delete...")
        msg.setInformativeText(f"Are you sure you want to delete that {item_name}?\n"
                               + f"{item_content}")
        msg.exec_()
        self.showListWidget.update()

        if msg.clickedButton() == yes_button:
            if item_name == 'map':
                city = self.showListWidget.takeItem(self.current_item_index + 1).text()
                city = city[:city.index('\t')]
                self.info.delete_node(city)
                self.update_map_on_showListWidget()
            elif item_name == 'order':
                if self.info[self.current_item_index].car is not None:
                    self.info[self.current_item_index].car.is_available = True

                if self.info[self.current_item_index].driver is not None:
                    self.info[self.current_item_index].driver.is_available = True

                del self.info[self.current_item_index]
                self.showListWidget.takeItem(self.current_item_index + 1)
            else:
                del self.info[self.current_item_index]
                self.showListWidget.takeItem(self.current_item_index + 1)
            self.update_signal.emit()

        elif msg.clickedButton() == no_button:
            msg.close()

    def update_map_on_showListWidget(self):
        self.clear_list_widget()
        info = self.user.get_map(self.info)

        self.add_to_list_widget(info[0], info[1])

    def validate_orders(self):
        if self.statusComboBox.isHidden() or self.user is None:
            return

        self.clear_list_widget()
        text = self.statusComboBox.currentText()
        additional = ''
        if text != 'All':
            additional = text.lower()

        info = self.user.get_orders(self.info, Order_status[text])
        self.add_to_list_widget(info[0], info[1], additional)


