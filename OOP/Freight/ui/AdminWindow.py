from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from ui.CustomMessagebox import create_msgbox
from PyQt5 import QtWidgets


class AdminWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app

    def setupUi(self, AdminWindow):
        AdminWindow.setObjectName("AdminWindow")
        AdminWindow.resize(394, 301)
        AdminWindow.setFixedSize(AdminWindow.size())
        self.centralwidget = QtWidgets.QWidget(AdminWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.logoutButton = QtWidgets.QPushButton(self.centralwidget)
        self.logoutButton.setGeometry(QtCore.QRect(0, 250, 81, 32))
        self.logoutButton.setObjectName("logoutButton")
        self.helpButton = QtWidgets.QPushButton(self.centralwidget)
        self.helpButton.setGeometry(QtCore.QRect(340, 250, 51, 32))
        self.helpButton.setObjectName("helpButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(140, 10, 121, 31))
        font = QtGui.QFont()
        font.setPointSize(16)
        font.setBold(True)
        font.setItalic(False)
        font.setWeight(75)
        font.setStrikeOut(False)
        font.setKerning(True)
        font.setStyleStrategy(QtGui.QFont.NoAntialias)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(50, 40, 296, 214))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.showAlterMapButton = QtWidgets.QPushButton(self.layoutWidget)
        self.showAlterMapButton.setObjectName("showAlterMapButton")
        self.gridLayout_2.addWidget(self.showAlterMapButton, 0, 0, 1, 1)
        self.showAlterCarsButton = QtWidgets.QPushButton(self.layoutWidget)
        self.showAlterCarsButton.setObjectName("showAlterCarsButton")
        self.gridLayout_2.addWidget(self.showAlterCarsButton, 2, 0, 1, 1)
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.showAlterOrdersButton = QtWidgets.QPushButton(self.layoutWidget)
        self.showAlterOrdersButton.setObjectName("showAlterOrdersButton")
        self.gridLayout.addWidget(self.showAlterOrdersButton, 0, 0, 1, 1)
        self.makeOrderButton = QtWidgets.QPushButton(self.layoutWidget)
        self.makeOrderButton.setObjectName("makeOrderButton")
        self.gridLayout.addWidget(self.makeOrderButton, 0, 1, 1, 1)
        self.gridLayout_2.addLayout(self.gridLayout, 4, 0, 1, 1)
        self.showAlterBudgetButton = QtWidgets.QPushButton(self.layoutWidget)
        self.showAlterBudgetButton.setObjectName("showAlterBudgetButton")
        self.gridLayout_2.addWidget(self.showAlterBudgetButton, 5, 0, 1, 1)
        self.createUserButton = QtWidgets.QPushButton(self.layoutWidget)
        self.createUserButton.setObjectName("createUserButton")
        self.gridLayout_2.addWidget(self.createUserButton, 6, 0, 1, 1)
        self.showAlterDriversButton = QtWidgets.QPushButton(self.layoutWidget)
        self.showAlterDriversButton.setObjectName("showAlterDriversButton")
        self.gridLayout_2.addWidget(self.showAlterDriversButton, 3, 0, 1, 1)
        AdminWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(AdminWindow)
        self.statusbar.setObjectName("statusbar")
        AdminWindow.setStatusBar(self.statusbar)

        self.retranslateUi(AdminWindow)
        QtCore.QMetaObject.connectSlotsByName(AdminWindow)

        # Signal-slot handlers
        self.logoutButton.clicked.connect(lambda: self.logout_clicked())
        self.helpButton.clicked.connect(lambda: self.help_button_clicked())

        self.makeOrderButton.clicked.connect(lambda: self.my_app.view_make_order_window())
        self.showAlterMapButton.clicked.connect(lambda: self.my_app.view_show_window("map"))
        self.showAlterDriversButton.clicked.connect(lambda: self.my_app.view_show_window("drivers"))
        self.showAlterCarsButton.clicked.connect(lambda: self.my_app.view_show_window("cars"))
        self.showAlterBudgetButton.clicked.connect(lambda: self.my_app.view_show_window("budget"))
        self.showAlterOrdersButton.clicked.connect(lambda: self.my_app.view_show_window("orders"))
        self.createUserButton.clicked.connect(lambda: self.my_app.view_input_window("user"))

    def retranslateUi(self, AdminWindow):
        _translate = QtCore.QCoreApplication.translate
        AdminWindow.setWindowTitle(_translate("AdminWindow", "MainWindow"))
        self.logoutButton.setText(_translate("AdminWindow", "Log out"))
        self.helpButton.setText(_translate("AdminWindow", "?"))
        self.label.setText(_translate("AdminWindow", "Admin mode"))
        self.showAlterMapButton.setText(_translate("AdminWindow", "Show map"))
        self.showAlterCarsButton.setText(_translate("AdminWindow", "Show cars"))
        self.showAlterOrdersButton.setText(_translate("AdminWindow", "Show orders"))
        self.makeOrderButton.setText(_translate("AdminWindow", "Make an order"))
        self.showAlterBudgetButton.setText(_translate("AdminWindow", "Show budget"))
        self.createUserButton.setText(_translate("AdminWindow", "Create a user"))
        self.showAlterDriversButton.setText(_translate("AdminWindow", "Show drivers"))

    def logout_clicked(self):
        msg = QtWidgets.QMessageBox()
        msg.setIcon(QtWidgets.QMessageBox.Question)
        yes_button = msg.addButton(QtWidgets.QMessageBox.Yes)
        no_button = msg.addButton(QtWidgets.QMessageBox.No)
        msg.setWindowTitle("Warning")
        msg.setText("Warning")
        msg.setInformativeText("Are you sure you want to logout?")
        msg.exec_()

        if msg.clickedButton() == yes_button:
            self.my_app.view_login_window()
        elif msg.clickedButton() == no_button:
            return

    def help_button_clicked(self):
        create_msgbox(QtWidgets.QMessageBox.Information, 'Information', "You're in admin mode\nAdditional info☟",
                      "Map button         →   show or alter map\n"
                      + "Cars button        →   show or alter cars\n"
                      + "Drivers button   →   show or alter drivers\n"
                      + "Orders buttons  →   show or alter orders\n"
                      + "Budget button   →   show budget\n"
                      + "User button        →   add a user\n")