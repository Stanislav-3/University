from transition import Transition
import time
import os
import threading
from PyQt5.QtCore import QTimer, QThread, pyqtSignal
import random


def try_to_transit(transitions, delay=1, parent=None):
    if len(transitions) == 0:
        return

    transition = random.choice(list(transitions))

    if not transition.can_transit():
        print('cannot transit', transition.id)
        return

    transition.decrement_sources_marks()
    transition.transit(delay, parent=parent)

    timer = QTimer(parent)
    timer.timeout.connect(transition.increment_target_marks)
    timer.setSingleShot(True)
    timer.start(delay * 1000)


class PetriNetQThread(QThread):
    transitSignal = pyqtSignal()

    def __init__(self, thread_delay=1):
        super(PetriNetQThread, self).__init__()
        self.delay = thread_delay

    def run(self):
        while True:
            self.transitSignal.emit()
            time.sleep(self.delay)

    def stop(self):
        self.terminate()
        self.wait()