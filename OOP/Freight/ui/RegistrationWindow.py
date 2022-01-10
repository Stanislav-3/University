from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from ui.CustomMessagebox import create_msgbox


class RegistrationWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app
        self.easter_egg = [0, 0]

    def setupUi(self, RegistrationWindow):
        RegistrationWindow.setObjectName("RegistrationWindow")
        RegistrationWindow.resize(160, 142)
        RegistrationWindow.setFixedSize(RegistrationWindow.size())
        self.centralwidget = QtWidgets.QWidget(RegistrationWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.helpButton = QtWidgets.QPushButton(self.centralwidget)
        self.helpButton.setGeometry(QtCore.QRect(110, 90, 51, 32))
        self.helpButton.setObjectName("helpButton")
        self.loginButton = QtWidgets.QPushButton(self.centralwidget)
        self.loginButton.setGeometry(QtCore.QRect(10, 50, 141, 32))
        self.loginButton.setObjectName("loginButton")
        self.welcomeLabel = QtWidgets.QLabel(self.centralwidget)
        self.welcomeLabel.setGeometry(QtCore.QRect(40, 20, 81, 20))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setItalic(False)
        font.setUnderline(False)
        font.setWeight(75)
        font.setStrikeOut(False)
        font.setKerning(True)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.welcomeLabel.setFont(font)
        self.welcomeLabel.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.welcomeLabel.setScaledContents(False)
        self.welcomeLabel.setObjectName("welcomeLabel")
        self.Button = QtWidgets.QPushButton(self.centralwidget)
        self.Button.setGeometry(QtCore.QRect(0, 0, 51, 31))
        self.Button.setObjectName("Button")
        self.Button_2 = QtWidgets.QPushButton(self.centralwidget)
        self.Button_2.setGeometry(QtCore.QRect(110, 0, 51, 31))
        self.Button_2.setObjectName("Button_2")
        self.Button_3 = QtWidgets.QPushButton(self.centralwidget)
        self.Button_3.setGeometry(QtCore.QRect(0, 90, 51, 31))
        self.Button_3.setObjectName("Button_3")
        self.Button.setFlat(True)
        self.Button_2.setFlat(True)
        self.Button_3.setFlat(True)
        RegistrationWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(RegistrationWindow)
        self.statusbar.setObjectName("statusbar")
        RegistrationWindow.setStatusBar(self.statusbar)

        self.retranslateUi(RegistrationWindow)
        QtCore.QMetaObject.connectSlotsByName(RegistrationWindow)

        # add events handler
        self.helpButton.clicked.connect(lambda: self.help_button_clicked())
        self.loginButton.clicked.connect(lambda: self.my_app.view_login_window())
        self.Button.clicked.connect(lambda: self.hiddenButton_clicked(1))
        self.Button_2.clicked.connect(lambda: self.hiddenButton_clicked(2))
        self.Button_3.clicked.connect(lambda: self.hiddenButton_clicked(3))

    def retranslateUi(self, RegistrationWindow):
        _translate = QtCore.QCoreApplication.translate
        RegistrationWindow.setWindowTitle(_translate("RegistrationWindow", "Freight app"))
        self.helpButton.setText(_translate("RegistrationWindow", "?"))
        self.loginButton.setText(_translate("RegistrationWindow", "Log in"))
        self.welcomeLabel.setText(_translate("RegistrationWindow", "Welcome!"))
        self.Button.setText(_translate("RegistrationWindow", ""))
        self.Button_2.setText(_translate("RegistrationWindow", ""))
        self.Button_3.setText(_translate("RegistrationWindow", ""))

    def help_button_clicked(self):
        create_msgbox(QtWidgets.QMessageBox.Information, "Freight app...", "Developed by Stanislav Korenevsky",
                      "This app is to manage freight transportation\n\n"
                      "Click \"log in\" to start managing...")

    def hiddenButton_clicked(self, num):
        if num == 1:
            if self.easter_egg == [0, 0]:
                self.easter_egg = [1, 0]
            else:
                self.easter_egg = [0, 0]
        elif num == 2:
            if self.easter_egg == [1, 0]:
                self.easter_egg = [1, 1]
            else:
                self.easter_egg = [0, 0]
        else:
            if self.easter_egg == [1, 1]:
                create_msgbox(QtWidgets.QMessageBox.Information, 'Welcome to the hidden window!',
                              'Nice day :)')
            self.easter_egg = [0, 0]
