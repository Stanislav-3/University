from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from copy import copy

class InputWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app
        self.item = None
        self.text_1 = None
        self.text_2 = None
        self.text_3 = None
        self.text_4 = None


    def setupUi(self, InputWindow):
        InputWindow.setObjectName("InputWindow")
        InputWindow.resize(310, 219)
        InputWindow.setFixedSize(InputWindow.size())
        self.centralwidget = QtWidgets.QWidget(InputWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.returnButton = QtWidgets.QPushButton(self.centralwidget)
        self.returnButton.setGeometry(QtCore.QRect(0, 170, 71, 32))
        self.returnButton.setObjectName("returnButton")
        self.titleLable = QtWidgets.QLabel(self.centralwidget)
        self.titleLable.setGeometry(QtCore.QRect(10, 10, 141, 20))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setWeight(75)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.titleLable.setFont(font)
        self.titleLable.setObjectName("titleLable")
        self.okButton = QtWidgets.QPushButton(self.centralwidget)
        self.okButton.setGeometry(QtCore.QRect(240, 170, 71, 32))
        self.okButton.setObjectName("okButton")
        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(32, 42, 249, 116))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.label_1 = QtWidgets.QLabel(self.layoutWidget)
        self.label_1.setObjectName("label_1")
        self.gridLayout.addWidget(self.label_1, 0, 0, 1, 1)
        self.lineEdit_1 = QtWidgets.QLineEdit(self.layoutWidget)
        self.lineEdit_1.setAcceptDrops(True)
        self.lineEdit_1.setText("")
        self.lineEdit_1.setObjectName("lineEdit_1")
        self.gridLayout.addWidget(self.lineEdit_1, 0, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.layoutWidget)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.lineEdit_2 = QtWidgets.QLineEdit(self.layoutWidget)
        self.lineEdit_2.setText("")
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.gridLayout.addWidget(self.lineEdit_2, 1, 1, 1, 1)
        self.label_3 = QtWidgets.QLabel(self.layoutWidget)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 2, 0, 1, 1)
        self.lineEdit_3 = QtWidgets.QLineEdit(self.layoutWidget)
        self.lineEdit_3.setText("")
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.gridLayout.addWidget(self.lineEdit_3, 2, 1, 1, 1)
        self.label_4 = QtWidgets.QLabel(self.layoutWidget)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 3, 0, 1, 1)
        self.lineEdit_4 = QtWidgets.QLineEdit(self.layoutWidget)
        self.lineEdit_4.setText("")
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.gridLayout.addWidget(self.lineEdit_4, 3, 1, 1, 1)
        InputWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(InputWindow)
        self.statusbar.setObjectName("statusbar")
        InputWindow.setStatusBar(self.statusbar)

        self.retranslateUi(InputWindow)
        QtCore.QMetaObject.connectSlotsByName(InputWindow)

        #events
        self.lineEdit_1.returnPressed.connect(lambda: self.lineEdit_2.setFocus())
        self.lineEdit_2.returnPressed.connect(lambda: self.lineEdit_3.setFocus())
        self.lineEdit_3.returnPressed.connect(lambda: self.manage_lineEdit_3_focus())

        self.lineEdit_4.returnPressed.connect(lambda: self.save_information())
        self.lineEdit_4.returnPressed.connect(lambda: self.my_app.try_to_add_item(self.item))

        self.okButton.clicked.connect(lambda: self.save_information())
        self.okButton.clicked.connect(lambda: self.my_app.try_to_add_item(self.item))

        self.returnButton.clicked.connect(lambda: self.returnButton_clicked())


    def retranslateUi(self, InputWindow):
        _translate = QtCore.QCoreApplication.translate
        InputWindow.setWindowTitle(_translate("InputWindow", "MainWindow"))
        self.returnButton.setText(_translate("InputWindow", "Return"))
        self.titleLable.setText(_translate("InputWindow", "Label"))
        self.okButton.setText(_translate("InputWindow", "Ok"))
        self.label_1.setText(_translate("InputWindow", "label_1"))
        self.label_2.setText(_translate("InputWindow", "label_2"))
        self.label_3.setText(_translate("InputWindow", "label_3"))
        self.label_4.setText(_translate("InputWindow", "label_4"))

    def manage_lineEdit_3_focus(self):
        if self.lineEdit_4.text() == "None":
            self.save_information()
            # return
        else:
            self.lineEdit_4.setFocus()

    def save_information(self):
        self.text_1 = self.lineEdit_1.text()
        self.text_2 = self.lineEdit_2.text()
        self.text_3 = self.lineEdit_3.text()
        self.text_4 = self.lineEdit_4.text()

    def initialize(self, item):
        self.lineEdit_1.setText("")
        self.lineEdit_2.setText("")
        self.lineEdit_3.setText("")
        self.lineEdit_4.setText("")
        self.lineEdit_1.setFocus()

        self.titleLable.setText(f"Add a new {item.lower()}:")
        if item == "user":
            self.label_4.hide()
            self.lineEdit_4.hide()

            self.label_1.setText("Login")
            self.label_2.setText("Password")
            self.label_3.setText("Mode (Admin/Operator)")
            self.item = "user"
        elif item == "driver":
            self.label_4.show()
            self.lineEdit_4.show()

            self.label_1.setText("Name")
            self.label_2.setText("Surname")
            self.label_3.setText("Middle name")
            self.label_4.setText("Driving experience")
            self.item = "drivers"
        elif item == "car":
            self.label_4.hide()
            self.lineEdit_4.hide()

            self.label_1.setText("Model")
            self.label_2.setText("Consumption (l/km)")
            self.label_3.setText("Max load (kg)")
            self.label_4.setText("None")
            self.item = "cars"
        else:
            self.label_4.show()
            self.lineEdit_4.show()

            self.label_1.setText("City 1")
            self.label_2.setText("City 2")
            self.label_3.setText("Distance (km)")
            self.label_4.setText("Max speed (km / h)")
            self.item = "map"

    def returnButton_clicked(self):
        if self.item == "user":
            self.my_app.view_user_window()
        else:
            self.my_app.view_show_window(self.item)