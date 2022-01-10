from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from ui.CustomMessagebox import create_msgbox
from PyQt5 import QtWidgets


class OperatorWindow(QMainWindow):
    def __init__(self, my_app):
        self.my_app = my_app

    def setupUi(self, OperatorWindow):
        OperatorWindow.setObjectName("OperatorWindow")
        OperatorWindow.resize(394, 301)
        OperatorWindow.setFixedSize(OperatorWindow.size())
        self.centralwidget = QtWidgets.QWidget(OperatorWindow)
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
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(70, 60, 263, 180))
        self.widget.setObjectName("widget")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.widget)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.showMapButton = QtWidgets.QPushButton(self.widget)
        self.showMapButton.setObjectName("showMapButton")
        self.gridLayout_2.addWidget(self.showMapButton, 0, 0, 1, 1)
        self.showDriversButton = QtWidgets.QPushButton(self.widget)
        self.showDriversButton.setObjectName("showDriversButton")
        self.gridLayout_2.addWidget(self.showDriversButton, 1, 0, 1, 1)
        self.showCarsButton = QtWidgets.QPushButton(self.widget)
        self.showCarsButton.setObjectName("showCarsButton")
        self.gridLayout_2.addWidget(self.showCarsButton, 2, 0, 1, 1)
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.showOrdersButton = QtWidgets.QPushButton(self.widget)
        self.showOrdersButton.setObjectName("showOrdersButton")
        self.gridLayout.addWidget(self.showOrdersButton, 0, 0, 1, 1)
        self.makeOrderButton = QtWidgets.QPushButton(self.widget)
        self.makeOrderButton.setObjectName("makeOrderButton")
        self.gridLayout.addWidget(self.makeOrderButton, 0, 1, 1, 1)
        self.gridLayout_2.addLayout(self.gridLayout, 3, 0, 1, 1)
        self.showBudgetButton = QtWidgets.QPushButton(self.widget)
        self.showBudgetButton.setObjectName("showBudgetButton")
        self.gridLayout_2.addWidget(self.showBudgetButton, 4, 0, 1, 1)
        OperatorWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(OperatorWindow)
        self.statusbar.setObjectName("statusbar")
        OperatorWindow.setStatusBar(self.statusbar)

        self.retranslateUi(OperatorWindow)
        QtCore.QMetaObject.connectSlotsByName(OperatorWindow)

        self.retranslateUi(OperatorWindow)
        QtCore.QMetaObject.connectSlotsByName(OperatorWindow)

        # Signal-slot handlers
        self.logoutButton.clicked.connect(lambda: self.logout_clicked())
        self.helpButton.clicked.connect(lambda: self.help_button_clicked())

        self.makeOrderButton.clicked.connect(lambda: self.my_app.view_make_order_window())
        self.showMapButton.clicked.connect(lambda: self.my_app.view_show_window("map"))
        self.showDriversButton.clicked.connect(lambda: self.my_app.view_show_window("drivers"))
        self.showCarsButton.clicked.connect(lambda: self.my_app.view_show_window("cars"))
        self.showBudgetButton.clicked.connect(lambda: self.my_app.view_show_window("budget"))
        self.showOrdersButton.clicked.connect(lambda: self.my_app.view_show_window("orders"))

    def retranslateUi(self, OperatorWindow):
        _translate = QtCore.QCoreApplication.translate
        OperatorWindow.setWindowTitle(_translate("OperatorWindow", "MainWindow"))
        self.logoutButton.setText(_translate("OperatorWindow", "Log out"))
        self.helpButton.setText(_translate("OperatorWindow", "?"))
        self.label.setText(_translate("OperatorWindow", "Operator mode"))
        self.showMapButton.setText(_translate("OperatorWindow", "Show map"))
        self.showDriversButton.setText(_translate("OperatorWindow", "Show drivers"))
        self.showCarsButton.setText(_translate("OperatorWindow", "Show cars"))
        self.showOrdersButton.setText(_translate("OperatorWindow", "Show orders"))
        self.makeOrderButton.setText(_translate("OperatorWindow", "Make an order"))
        self.showBudgetButton.setText(_translate("OperatorWindow", "Show budget"))

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
                      "Map button         →   show map\n"
                      + "Cars button        →   show cars\n"
                      + "Drivers button   →   show drivers\n"
                      + "Orders buttons  →   show or alter orders\n"
                      + "Budget button   →   show budget\n")