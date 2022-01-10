from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow

class LoginWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app
        self.login = None
        self.password = None

    def setupUi(self, LoginWindow):
        LoginWindow.setObjectName("LoginWindow")
        LoginWindow.resize(310, 203)
        LoginWindow.setFixedSize(LoginWindow.size())
        self.centralwidget = QtWidgets.QWidget(LoginWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.returnButton = QtWidgets.QPushButton(self.centralwidget)
        self.returnButton.setGeometry(QtCore.QRect(0, 150, 71, 32))
        self.returnButton.setObjectName("returnButton")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(100, 20, 121, 20))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setWeight(75)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.loginButton = QtWidgets.QPushButton(self.centralwidget)
        self.loginButton.setGeometry(QtCore.QRect(240, 150, 71, 32))
        self.loginButton.setObjectName("loginButton")
        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(40, 60, 231, 54))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.label = QtWidgets.QLabel(self.layoutWidget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.loginLineEdit = QtWidgets.QLineEdit(self.layoutWidget)
        self.loginLineEdit.setText("")
        self.loginLineEdit.setObjectName("loginLineEdit")
        self.gridLayout.addWidget(self.loginLineEdit, 0, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.layoutWidget)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.passwordLineEdit = QtWidgets.QLineEdit(self.layoutWidget)
        self.passwordLineEdit.setAutoFillBackground(False)
        self.passwordLineEdit.setText("")
        self.passwordLineEdit.setObjectName("passwordLineEdit")
        self.passwordLineEdit.setEchoMode(QtWidgets.QLineEdit.Password)
        self.gridLayout.addWidget(self.passwordLineEdit, 1, 1, 1, 1)
        LoginWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(LoginWindow)
        self.statusbar.setObjectName("statusbar")
        LoginWindow.setStatusBar(self.statusbar)

        self.retranslateUi(LoginWindow)
        QtCore.QMetaObject.connectSlotsByName(LoginWindow)

        # add events handler
        self.returnButton.clicked.connect(lambda: self.my_app.view_registration_window())
        self.loginLineEdit.returnPressed.connect(lambda: self.passwordLineEdit.setFocus())
        self.passwordLineEdit.returnPressed.connect(lambda: self.save_information_and_try_to_login())
        self.loginButton.clicked.connect(lambda: self.save_information_and_try_to_login())

    def retranslateUi(self, LoginWindow):
        _translate = QtCore.QCoreApplication.translate
        LoginWindow.setWindowTitle(_translate("LoginWindow", "MainWindow"))
        self.returnButton.setText(_translate("LoginWindow", "Return"))
        self.label_3.setText(_translate("LoginWindow", "Authorization"))
        self.loginButton.setText(_translate("LoginWindow", "Log in"))
        self.label.setText(_translate("LoginWindow", "Login:"))
        self.label_2.setText(_translate("LoginWindow", "Password:"))

    def save_information_and_try_to_login(self):
        self.login = self.loginLineEdit.text()
        self.password = self.passwordLineEdit.text()

        self.loginLineEdit.setText("")
        self.passwordLineEdit.setText("")
        self.loginLineEdit.setFocus()

        self.my_app.try_to_login()