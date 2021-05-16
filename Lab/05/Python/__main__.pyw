from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *

if __name__ == "__main__":
    from sys import argv, exit
    from window import MainWindow
    app = QApplication(argv)

    window = MainWindow()
    window.show()

    exit(app.exec_())