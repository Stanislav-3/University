import sys
from concurrent.futures.thread import ThreadPoolExecutor
from datetime import datetime, timedelta

from PyQt5 import QtWidgets
from PyQt5.QtCore import QObject, pyqtSignal

from ui.RegistrationWindow import RegistrationWindow
from ui.LoginWindow import LoginWindow
from ui.OperatorWindow import OperatorWindow
from ui.AdminWindow import AdminWindow
from ui.MakeOrderWindow import MakeOrderWindow
from ui.ShowWindow import ShowWindow
from ui.InputWindow import InputWindow
from ui.CustomMessagebox import create_msgbox

from users.operator import Operator
from users.admin import Admin

from company_info import CompanyInfo
from units.order.order_status import Order_status

from database.data_manager import DataManager

from timer.timer import Timer


class Application(QObject):
    update_orders_status = pyqtSignal()
    save_to_database = pyqtSignal()

    def __init__(self):
        # QT app initialization
        super(Application, self).__init__()
        self.app = QtWidgets.QApplication(sys.argv)

        # Load info from a database
        self.data_manager = DataManager()
        self.company_info = CompanyInfo()
        self.users = []
        self.current_user = None
        self.data_manager.initialize(self.users, self.company_info)

        # Timer
        self.check_orders_timer = Timer(self)
        self.check_orders_timer.connect_slot(self.check_orders_on_status)
        self.orders_check_timer_sec = 1
        self.check_orders_timer.start_timer(sec=self.orders_check_timer_sec)

        self.update_budget_timer = Timer(self)
        self.update_budget_timer.connect_slot(self.update_budget)
        self.update_time_min = 1
        self.update_budget_timer.start_timer(minutes=self.update_time_min, sec=0)

        # Connecting signals to slots
        self.update_orders_status.connect(self.check_orders_on_status)
        self.save_to_database.connect(lambda: self.data_manager.save_info(self.users, self.company_info))

        # Creating QMainWindow instances
        self.registration_window = QtWidgets.QMainWindow()
        self.login_window = QtWidgets.QMainWindow()
        self.operator_window = QtWidgets.QMainWindow()
        self.admin_window = QtWidgets.QMainWindow()
        self.make_order_window = QtWidgets.QMainWindow()
        self.show_window = QtWidgets.QMainWindow()
        self.input_window = QtWidgets.QMainWindow()

        # load UI's
        self.ui_registration_window = RegistrationWindow(self)
        self.ui_login_window = LoginWindow(self)
        self.ui_operator_window = OperatorWindow(self)
        self.ui_admin_window = AdminWindow(self)
        self.ui_make_order_window = MakeOrderWindow(self)
        self.ui_show_window = ShowWindow(self, self.save_to_database)
        self.ui_input_window = InputWindow(self)

        # set up UI's on QMainWindow's
        self.ui_registration_window.setupUi(self.registration_window)
        self.ui_login_window.setupUi(self.login_window)
        self.ui_operator_window.setupUi(self.operator_window)
        self.ui_admin_window.setupUi(self.admin_window)
        self.ui_make_order_window.setupUi(self.make_order_window)
        self.ui_show_window.setupUi(self.show_window)
        self.ui_input_window.setupUi(self.input_window)

        # Show QMainWindow with our UI
        self.registration_window.show()

        # app cycle
        sys.exit(self.app.exec_())

    def view_registration_window(self):
        self.login_window.hide()
        self.registration_window.show()

    def view_login_window(self):
        self.registration_window.hide()
        self.admin_window.hide()
        self.operator_window.hide()

        self.current_user = None
        self.login_window.show()

    def view_user_window(self):
        self.login_window.hide()
        self.make_order_window.hide()
        self.input_window.hide()
        self.show_window.hide()

        if isinstance(self.current_user, Admin):
            self.admin_window.show()
        else:
            self.operator_window.show()

    def view_make_order_window(self):
        self.admin_window.hide()
        self.operator_window.hide()
        self.make_order_window.show()

    def view_show_window(self, item: str):
        self.admin_window.hide()
        self.operator_window.hide()
        self.input_window.hide()

        if item == "drivers":
            self.ui_show_window.initialize(item, self.current_user, self.company_info.drivers)
        elif item == "cars":
            self.ui_show_window.initialize(item, self.current_user, self.company_info.cars)
        elif item == "budget":
            self.ui_show_window.initialize(item, self.current_user, self.company_info.budget)
        elif item == "orders":
            self.ui_show_window.initialize(item, self.current_user, self.company_info.orders)
        elif item == "map":
            self.ui_show_window.initialize(item, self.current_user, self.company_info.map)
        self.show_window.show()

    def view_input_window(self, item: str):
        self.admin_window.hide()
        self.operator_window.hide()
        self.show_window.hide()

        self.ui_input_window.initialize(item)
        self.input_window.show()

    def try_to_create_new_user(self, login: str, password: str, mode: str):
        try:
            user = None
            if mode == "Operator":
                user = Operator(login, password)
                self.users.append(user)
            elif mode == "Admin":
                user = Admin(login, password)
                self.users.append(user)
            else:
                ValueError(f"{mode.capitalize()} isn't available...")

            if user is not None:
                self.save_to_database.emit()

        except Exception as e:
            raise Exception("User is not added...")

    def try_to_login(self):
        login = self.ui_login_window.login
        password = self.ui_login_window.password
        user = None

        for i in range(len(self.users)):
            if self.users[i].login == login and self.users[i].get_password() == password:
                user = self.users[i]
                break

        if user is None:
            create_msgbox(QtWidgets.QMessageBox.Critical, "Error...", "That user doesn't exist!",
                          "You've entered:\n"
                          f"Login: \t{login}\n"
                          f"Password: \t{password}")
            return

        create_msgbox(QtWidgets.QMessageBox.Information, "Success!", f"Welcome, {login}")
        self.current_user = user
        self.view_user_window()

    def try_to_add_item(self, item):
        info_1 = self.ui_input_window.text_1
        info_2 = self.ui_input_window.text_2
        info_3 = self.ui_input_window.text_3
        info_4 = self.ui_input_window.text_4
        added = True
        if item == "map":
            try:
                self.company_info.add_city(info_1, info_2, info_3, info_4)
            except Exception as e:
                added = False
                create_msgbox(QtWidgets.QMessageBox.Critical, "Error...", f"{e}",
                              "Your input:\n"
                              f"City 1\t= {info_1}\n"
                              f"City 2\t= {info_2}\n"
                              f"Distance\t= {info_3}\n"
                              f"Max speed\t= {info_4}\n"
                              f"{e}")
        elif item == "drivers":
            try:
                self.company_info.add_driver(info_1, info_2, info_3, info_4)
            except Exception as e:
                added = False
                create_msgbox(QtWidgets.QMessageBox.Critical, "Error...", f"{e}",
                              "Your input:\n"
                              + f"Name\t\t= {info_1}\n"
                              + f"Surname\t\t= {info_2}\n"
                              + f"Middle name\t= {info_3}\n"
                              + f"Driving experience\t= {info_4}")
        elif item == "cars":
            try:
                self.company_info.add_car(info_1, info_2, info_3)
            except Exception as e:
                added = False
                create_msgbox(QtWidgets.QMessageBox.Critical, "Error...", f"{e}",
                              "Your input:\n"
                              f"Model\t\t= {info_1}\n"
                              f"Gas consumption\t= {info_2}\n"
                              f"Max load\t\t= {info_3}\n")
        elif item == "user":
            try:
                self.try_to_create_new_user(info_1, info_2, info_3)
            except Exception as e:
                added = False
                create_msgbox(QtWidgets.QMessageBox.Critical, "Error...", f"{e}",
                              "Your input:\n"
                              f"Login\t\t= {info_1}\n"
                              f"Password\t= {info_2}\n"
                              f"User mode\t= {info_3}\n")

        if added:
            self.save_to_database.emit()
            if item == "user":
                self.view_user_window()
            else:
                self.view_show_window(item)

    def make_order(self):
        origin = self.ui_make_order_window.origin
        destination = self.ui_make_order_window.destination
        arrival_date = self.ui_make_order_window.arrival_date
        load = self.ui_make_order_window.load
        experience_matters = self.ui_make_order_window.experience_matters

        try:
            self.current_user.form_order(self.company_info, origin, destination, arrival_date, load, experience_matters)
        except TimeoutError as e:
            create_msgbox(QtWidgets.QMessageBox.Critical, "Warning!..", "Order was canceled!",
                          f"The following problem is occurred:\n{e}")
            return
        except Exception as e:
            create_msgbox(QtWidgets.QMessageBox.Critical, "Warning!..", "Order was delayed!",
                          f"The following problem is occurred:\n{e}")
            return

        self.save_to_database.emit()
        create_msgbox(QtWidgets.QMessageBox.Information, "Success!", "Order is added :)",
                      f'Origin: {origin}\n'
                      f'Destination: {destination}\n'
                      f'Arrival date: {arrival_date}\n'
                      f'Load: {load}\n'
                      f'Experience matters: {experience_matters}')

    def check_orders_on_status(self):
        changed = False

        # Check whether the order is completed
        executing_orders = self.company_info.get_orders(Order_status.Executing)
        for i in range(len(executing_orders)):
            if executing_orders[i].arrival_datetime < datetime.now():
                order = executing_orders[i]
                order.complete_order()
                create_msgbox(QtWidgets.QMessageBox.Information, "Information!..", "Order is completed!",
                              f'Origin: {order.origin}\n'
                              f'Destination: {order.destination}\n'
                              f'Arrival date: {order.arrival_datetime}\n'
                              f'Load: {order.load}\n'
                              f'Experience matters: {order.experience_matters}')
                changed = True

        # Try to execute delayed orders
        reserved_orders = self.company_info.get_orders(Order_status.Reserved)
        for i in range(len(reserved_orders)):
            order = reserved_orders[i]
            res = None
            try:
                if self.current_user is not None:
                    res = self.current_user.form_order(self.company_info, order=order)

            # Not enough time is left for order execution
            except TimeoutError as e:
                create_msgbox(QtWidgets.QMessageBox.Critical, "Warning!..", "Order was canceled!",
                              f"The following problem is occurred:\n{e}")
                changed = True

            # Order cannot be executed yet
            except Exception as e:
                # create_msgbox(QtWidgets.QMessageBox.Information, "Warning!..", "Order was delayed!",
                #               f"The following problem is occurred:\n{e}")
                # changed = True
                pass

            # Delayed order is started executing
            if res is not None:
                create_msgbox(QtWidgets.QMessageBox.Information, "Information!..", "Delayed order is started executing",
                              f'Origin: {order.origin}\n'
                              f'Destination: {order.destination}\n'
                              f'Arrival date: {order.arrival_datetime}\n'
                              f'Load: {order.load}\n'
                              f'Experience matters: {order.experience_matters}')
                changed = True

        if changed:
            self.save_to_database.emit()
            self.ui_show_window.validate_orders()

    def update_budget(self):
        income = 0
        dt1 = datetime.now()
        dt0 = dt1 - timedelta(minutes=self.update_time_min, seconds=self.orders_check_timer_sec)

        orders = self.company_info.get_orders(Order_status.Completed)
        for i in range(len(orders)):
            if orders[i].arrival_datetime > dt0:
                income += orders[i].money

        if income != 0:
            self.company_info.add_budget(income, dt0, dt1)