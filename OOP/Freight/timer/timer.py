from PyQt5.QtCore import QObject, pyqtSignal, QTimer


class Timer(QObject):
    timout = pyqtSignal()

    def __init__(self, parent):
        super(Timer, self).__init__()
        self.timer = QTimer(parent)
        self.timer.timeout.connect(self.emit_signal)

    def emit_signal(self):
        self.timout.emit()

    def connect_slot(self, func):
        self.timout.connect(func)

    def start_timer(self, minutes=0, sec=1):
        msecs = (minutes * 60 + sec) * 10**3
        self.timer.start(msecs)

    def stop_timer(self):
        self.timer.stop()