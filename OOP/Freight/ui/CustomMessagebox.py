from PyQt5 import QtWidgets


def create_msgbox(icon: QtWidgets.QMessageBox, title: str, text: str, detailed_text: str = None):
    msg = QtWidgets.QMessageBox()

    msg.setIcon(icon)
    msg.setWindowTitle(title)
    msg.setText(title)
    msg.setInformativeText(text)
    if detailed_text is not None:
        msg.setDetailedText(detailed_text)

    msg.exec_()