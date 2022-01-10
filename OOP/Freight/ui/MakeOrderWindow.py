from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow

class MakeOrderWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app
        self.origin = None
        self.destination = None
        self.arrival_dateLineEdit = None
        self.loadLineEdit = None
        self.experience_matters = None

    def setupUi(self, MakeOrderWindow):
        MakeOrderWindow.setObjectName("MakeOrderWindow")
        MakeOrderWindow.resize(310, 241)
        MakeOrderWindow.setFixedSize(MakeOrderWindow.size())
        self.centralwidget = QtWidgets.QWidget(MakeOrderWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.returnButton = QtWidgets.QPushButton(self.centralwidget)
        self.returnButton.setGeometry(QtCore.QRect(0, 190, 71, 32))
        self.returnButton.setObjectName("returnButton")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(100, 10, 121, 20))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setWeight(75)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.Button = QtWidgets.QPushButton(self.centralwidget)
        self.Button.setGeometry(QtCore.QRect(240, 190, 71, 32))
        self.Button.setObjectName("Button")
        self.experienceMattersCheckBox = QtWidgets.QCheckBox(self.centralwidget)
        self.experienceMattersCheckBox.setEnabled(True)
        self.experienceMattersCheckBox.setGeometry(QtCore.QRect(50, 160, 191, 20))
        font = QtGui.QFont()
        font.setStrikeOut(False)
        self.experienceMattersCheckBox.setFont(font)
        self.experienceMattersCheckBox.setChecked(True)
        self.experienceMattersCheckBox.setAutoRepeat(False)
        self.experienceMattersCheckBox.setObjectName("experienceMattersCheckBox")
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(50, 40, 209, 116))
        self.widget.setObjectName("widget")
        self.gridLayout = QtWidgets.QGridLayout(self.widget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.label_4 = QtWidgets.QLabel(self.widget)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 0, 0, 1, 1)
        self.originLineEdit = QtWidgets.QLineEdit(self.widget)
        self.originLineEdit.setText("")
        self.originLineEdit.setObjectName("originLineEdit")
        self.gridLayout.addWidget(self.originLineEdit, 0, 1, 1, 1)
        self.label = QtWidgets.QLabel(self.widget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)
        self.destinationLineEdit = QtWidgets.QLineEdit(self.widget)
        self.destinationLineEdit.setText("")
        self.destinationLineEdit.setObjectName("destinationLineEdit")
        self.gridLayout.addWidget(self.destinationLineEdit, 1, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.widget)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 2, 0, 1, 1)
        self.arrival_dateLineEdit = QtWidgets.QLineEdit(self.widget)
        self.arrival_dateLineEdit.setText("")
        self.arrival_dateLineEdit.setObjectName("arrival_dateLineEdit")
        self.gridLayout.addWidget(self.arrival_dateLineEdit, 2, 1, 1, 1)
        self.label_5 = QtWidgets.QLabel(self.widget)
        self.label_5.setObjectName("label_5")
        self.gridLayout.addWidget(self.label_5, 3, 0, 1, 1)
        self.loadLineEdit = QtWidgets.QLineEdit(self.widget)
        self.loadLineEdit.setText("")
        self.loadLineEdit.setObjectName("loadLineEdit")
        self.gridLayout.addWidget(self.loadLineEdit, 3, 1, 1, 1)
        MakeOrderWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MakeOrderWindow)
        self.statusbar.setObjectName("statusbar")
        MakeOrderWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MakeOrderWindow)
        QtCore.QMetaObject.connectSlotsByName(MakeOrderWindow)

        # add events handler
        self.originLineEdit.returnPressed.connect(lambda: self.destinationLineEdit.setFocus())
        self.destinationLineEdit.returnPressed.connect(lambda: self.arrival_dateLineEdit.setFocus())
        self.arrival_dateLineEdit.returnPressed.connect(lambda: self.loadLineEdit.setFocus())
        self.loadLineEdit.returnPressed.connect(lambda: self.loadLineEdit.clearFocus())

        self.returnButton.clicked.connect(lambda: self.my_app.view_user_window())

        self.Button.clicked.connect(lambda: self.save_information())
        self.Button.clicked.connect(lambda: self.my_app.make_order())

    def retranslateUi(self, MakeOrderWindow):
        _translate = QtCore.QCoreApplication.translate
        MakeOrderWindow.setWindowTitle(_translate("MakeOrderWindow", "MainWindow"))
        self.returnButton.setText(_translate("MakeOrderWindow", "Return"))
        self.label_3.setText(_translate("MakeOrderWindow", "Make an order"))
        self.Button.setText(_translate("MakeOrderWindow", "Ok"))
        self.experienceMattersCheckBox.setText(_translate("MakeOrderWindow", "Driver\'s experience matters"))
        self.label_4.setText(_translate("MakeOrderWindow", "Origin:"))
        self.label.setText(_translate("MakeOrderWindow", "Destination:"))
        self.label_2.setText(_translate("MakeOrderWindow", "Arrival date:"))
        self.label_5.setText(_translate("MakeOrderWindow", "Load:"))

    def clear_information(self):
        self.originLineEdit.setText('')
        self.destinationLineEdit.setText('')
        self.arrival_dateLineEdit.setText('')
        self.loadLineEdit.setText('')
        self.experienceMattersCheckBox.setChecked(True)
        self.originLineEdit.setFocus()

    def save_information(self):
        self.origin = self.originLineEdit.text()
        self.destination = self.destinationLineEdit.text()
        self.arrival_date = self.arrival_dateLineEdit.text()
        self.load = self.loadLineEdit.text()
        self.experience_matters = self.experienceMattersCheckBox.isChecked()

        self.clear_information()
