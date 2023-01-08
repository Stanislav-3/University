from PyQt5.QtWidgets import *
import sys

from computations import compute


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi()

        self.radioButton1 = QRadioButton('Generator 1', self)
        self.radioButton2 = QRadioButton('Generator 2', self)
        self.radioButton3 = QRadioButton('Generator 3', self)
        self.radioButton4 = QRadioButton('Generator 4', self)

        self.current_generator = 1

        self.radioButton1.setChecked(True)

        radio_button_x_start, radio_button_y_start = 10, 10
        radio_button_y_delta = 30

        self.radioButton1.move(radio_button_x_start, radio_button_y_start)
        self.radioButton2.move(radio_button_x_start, radio_button_y_start + radio_button_y_delta)
        self.radioButton3.move(radio_button_x_start, radio_button_y_start + radio_button_y_delta * 2)
        self.radioButton4.move(radio_button_x_start, radio_button_y_start + radio_button_y_delta * 3)

        self.calculateButton = QPushButton('Calculate', self)
        self.calculateButton.move(radio_button_x_start, radio_button_y_start + radio_button_y_delta * 4)

        self.input = QLineEdit(self)
        self.input_label = QLabel(self)

        input_zone_x_start, input_zone_y_start = 200, 10
        input_label_x, input_label_y = 200, 40

        self.input_label.resize(input_label_x, input_label_y)
        self.input_label.move(input_zone_x_start, input_zone_y_start)

        self.generator1_label_text = 'Input probability\n(e.g.  0.5)'
        self.generator2_label_text = 'Input array of probabilities\n(e.g.  0.2, 0.6, 0.3)'
        self.generator3_label_text = 'Input P(A) and P(B|A)\n(e.g.  0.2, 0.6)'
        self.generator4_label_text = 'Input array of exhaustive\nprobabilities  (e.g.  0.1, 0.6, 0.3)'

        self.input_label.setText(self.generator1_label_text)

        self.input.resize(input_label_x, input_label_y)
        self.input.move(input_zone_x_start, input_zone_y_start + input_label_y + 10)

        # Output label
        self.output_label = QLabel(self)
        self.output_label.resize(550, 20)
        self.output_label.move(input_zone_x_start + input_label_x + 50, input_zone_y_start)
        self.output_label_default_text = 'Your computations will be there'
        self.output_label.setText(self.output_label_default_text)

        # Events handlers
        self.radioButton1.clicked.connect(self.radioButton_handler)
        self.radioButton2.clicked.connect(self.radioButton_handler)
        self.radioButton3.clicked.connect(self.radioButton_handler)
        self.radioButton4.clicked.connect(self.radioButton_handler)

        self.calculateButton.clicked.connect(self.calculateButton_handler)

    def setupUi(self):
        self.setWindowTitle("Hello, world")
        self.resize(1000, 500)

    def radioButton_handler(self):
        if self.radioButton1.isChecked():
            self.input_label.setText(self.generator1_label_text)
            self.output_label.resize(550, 20)
            self.output_label.setText(self.output_label_default_text)
            self.current_generator = 1
        elif self.radioButton2.isChecked():
            self.input_label.setText(self.generator2_label_text)
            self.output_label.resize(550, 20)
            self.output_label.setText(self.output_label_default_text)
            self.current_generator = 2
        elif self.radioButton3.isChecked():
            self.input_label.setText(self.generator3_label_text)
            self.output_label.resize(550, 20)
            self.output_label.setText(self.output_label_default_text)
            self.current_generator = 3
        elif self.radioButton4.isChecked():
            self.input_label.setText(self.generator4_label_text)
            self.output_label.resize(550, 20)
            self.output_label.setText(self.output_label_default_text)
            self.current_generator = 4

    def calculateButton_handler(self):
        try:
            result = compute(self.current_generator, self.input.text())
        except Exception as e:
            self.output_label.setText(e.__str__())
            return

        if self.radioButton1.isChecked():
            self.output_label.resize(550, 20 * 2)
            self.output_label.setText(f'False:\t{result[0]}\nTrue:\t{result[1]}')
        elif self.radioButton2.isChecked():
            result_text = ''
            for i in range(len(result)):
                separator = ',\t' if i % 3 != 2 else '\n'
                separator = '' if i == len(result) - 1 else separator

                result_text += f'{result[i]}{separator}'

            self.output_label.resize(550, 20 * (len(result) / 3 + int(len(result) % 3 != 0)))
            self.output_label.setText(result_text)
        elif self.radioButton3.isChecked():
            computational, analytical = result
            self.output_label.resize(550, 20 * 5)
            self.output_label.setText(f'\tComputational\t\t\tAnalytical\n'
                                      f'AB\t{computational[0]}\t\t{analytical[0]}\n'
                                      f'AB̅\t{computational[1]}\t\t{analytical[1]}\n'
                                      f'A̅B\t{computational[2]}\t\t{analytical[2]}\n'
                                      f'A̅B̅\t{computational[3]}\t\t{analytical[3]}\n')
        elif self.radioButton4.isChecked():
            result_text = ''
            for i in range(len(result)):
                separator = ',\t' if i % 3 != 2 else '\n'
                separator = '' if i == len(result) - 1 else separator

                result_text += f'{result[i]}{separator}'

            self.output_label.resize(550, 20 * (len(result) / 3 + int(len(result) % 3 != 0)))
            self.output_label.setText(result_text)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
