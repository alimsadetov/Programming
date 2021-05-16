# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'windowEksWCI.ui'
##
## Created by: Qt User Interface Compiler version 6.0.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *

from utils import to_bits, write_bytes, read_bytes


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(384, 220)
        MainWindow.setWindowTitle(u"\u0421\u0442\u0435\u043d\u043e\u0433\u0440\u0430\u0444")
        icon = QIcon()
        icon.addFile("typewriter.png", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.central_widget = QWidget(MainWindow)
        self.central_widget.setObjectName(u"central_widget")
        self.vertical_layout = QVBoxLayout(self.central_widget)
        self.vertical_layout.setObjectName(u"vertical_layout")
        self.horizontal_layout = QHBoxLayout()
        self.horizontal_layout.setObjectName(u"horizontal_layout")

        self.vertical_layout.addLayout(self.horizontal_layout)

        self.text_edit = QPlainTextEdit(self.central_widget)
        self.text_edit.setObjectName(u"text_edit")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.text_edit.sizePolicy().hasHeightForWidth())
        self.text_edit.setSizePolicy(sizePolicy)

        self.vertical_layout.addWidget(self.text_edit)

        self.load_button = QPushButton(self.central_widget)
        self.load_button.setObjectName(u"load_button")

        self.vertical_layout.addWidget(self.load_button)

        self.output_label = QLabel(self.central_widget)
        self.output_label.setObjectName(u"output_label")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.output_label.sizePolicy().hasHeightForWidth())
        self.output_label.setSizePolicy(sizePolicy1)
        self.output_label.setScaledContents(False)
        self.output_label.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignTop)
        self.output_label.setWordWrap(True)

        self.vertical_layout.addWidget(self.output_label)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.decode_button = QPushButton(self.central_widget)
        self.decode_button.setObjectName(u"decode_button")

        self.horizontalLayout_2.addWidget(self.decode_button)

        self.encode_button = QPushButton(self.central_widget)
        self.encode_button.setObjectName(u"encode_button")

        self.horizontalLayout_2.addWidget(self.encode_button)

        self.vertical_layout.addLayout(self.horizontalLayout_2)

        self.save_button = QPushButton(self.central_widget)
        self.save_button.setObjectName(u"save_button")

        self.vertical_layout.addWidget(self.save_button)

        MainWindow.setCentralWidget(self.central_widget)
        QWidget.setTabOrder(self.encode_button, self.decode_button)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)

    # setupUi

    def retranslateUi(self, MainWindow):
        self.text_edit.setPlaceholderText(QCoreApplication.translate("MainWindow",
                                                                     u"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0442\u0435\u043a\u0441\u0442...",
                                                                     None))
        self.load_button.setText(QCoreApplication.translate("MainWindow",
                                                            u"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u0438\u0437\u043e\u0431\u0440\u0430\u0436\u0435\u043d\u0438\u0435",
                                                            None))
        self.output_label.setText(QCoreApplication.translate("MainWindow",
                                                             u"\u0421\u044e\u0434\u0430 \u0431\u0443\u0434\u0443\u0442 \u0432\u044b\u0432\u043e\u0434\u0438\u0442\u044c\u0441\u044f \u0443\u0432\u0435\u0434\u043e\u043c\u043b\u0435\u043d\u0438\u044f",
                                                             None))
        self.decode_button.setText(QCoreApplication.translate("MainWindow",
                                                              u"\u0414\u0435\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442",
                                                              None))
        self.encode_button.setText(QCoreApplication.translate("MainWindow",
                                                              u"\u041a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442",
                                                              None))
        self.save_button.setText(QCoreApplication.translate("MainWindow",
                                                            u"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u0438\u0437\u043e\u0431\u0440\u0430\u0436\u0435\u043d\u0438\u0435",
                                                            None))
        pass
    # retranslateUi


class CryptData:
    def __init__(self):
        self.current = 0
        self.capacity = 0

    def less(self):
        return self.current < self.capacity

    def maximum(self):
        return self.current == self.capacity

    def overflow(self):
        return self.current > self.capacity

    def difference(self):
        return self.capacity - self.current

    def rdifference(self):
        return self.current - self.capacity


class MainWindow(QMainWindow):
    CryptKey = bytes((0b11100010, 0b10011101, 0b10100100))
    Length = 4

    def __init__(self):
        super(MainWindow, self).__init__(None)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.image = None
        self.data = CryptData()

        self.ui.output_label.setWordWrap(True)

        self.ui.text_edit.textChanged.connect(self.message_changed)
        self.ui.load_button.clicked.connect(self.read_image)
        self.ui.save_button.clicked.connect(self.write_image)

        self.ui.encode_button.clicked.connect(self.encode_text)
        self.ui.decode_button.clicked.connect(self.decode_text)

        self.reset_state()

    def clear_image(self):
        if not self.image:
            return

        del self.image
        self.image = None

    def reset_state(self):
        self.clear_image()
        self.update_activity_state()

    def update_activity_state(self):
        active = self.image is not None

        self.ui.text_edit.setEnabled(active)
        self.ui.save_button.setEnabled(active)
        self.ui.decode_button.setEnabled(active)
        self.ui.encode_button.setEnabled(active)

    def get_input(self):
        return self.ui.text_edit.toPlainText()

    @Slot()
    def read_image(self):
        filepath, _ = QFileDialog.getOpenFileName(self, "Открыть картинку", "", "Допустимые форматы (*.png)")

        if not filepath:
            return

        self.reset_state()

        if not QFile.exists(filepath):
            self.set_output_message(f"Изображение '{filepath}' не найдено!")
            return

        self.image = QImage()
        if not self.image.load(filepath):
            self.set_output_message(f"Изображение '{filepath}' не загружено!")
            self.clear_image()
            return

        self.image.convertTo(QImage.Format_ARGB32)

        self.data.capacity = (self.image.width() * self.image.height() * 3) // 8 - len(
            MainWindow.CryptKey) - MainWindow.Length

        self.set_output_message("Изображение успешно загружено")
        self.update_activity_state()

    @Slot()
    def write_image(self):
        if self.image is None:
            self.set_output_message("Изображение не загружено в программу!")
            return

        filepath, _ = QFileDialog.getSaveFileName(self, "Сохранить картинку", "", "Допустимые форматы (*.png)")

        if self.image.save(filepath, "PNG"):
            self.set_output_message(f"Изображение успешно сохранено в {filepath}")
            return

        self.set_output_message("Изображение не сохранено")

    @Slot()
    def encode_text(self):
        if self.image is None:
            self.set_output_message("Изображение не загружено в программу!")
            return

        array = QByteArray()
        array.push_back(self.get_input().encode())

        self.data.current = len(array)

        if self.data.overflow():
            self.set_output_message("Недостаточно места для кодирования!")
            return

        for i in range(MainWindow.Length):
            array.push_front(bytes(((self.data.current >> to_bits(i)) & 0xff,)))

        for i in range(len(MainWindow.CryptKey) - 1, -1, -1):
            array.push_front(bytes((MainWindow.CryptKey[i],)))

        write_bytes(self.image, array, 0)

        self.set_output_message("Сообщение добавлено в изображение!")

    @Slot()
    def decode_text(self):
        if self.image is None:
            self.set_output_message("Изображение не загружено в программу!")
            return

        header = len(MainWindow.CryptKey) + MainWindow.Length

        array = read_bytes(self.image, 0, header)

        for i in range(0, len(MainWindow.CryptKey)):
            if bytes((MainWindow.CryptKey[i],)) != array[i]:
                self.set_output_message("Сообщение отсутствует!")
                return

        size = 0

        for i in range(len(MainWindow.CryptKey), len(MainWindow.CryptKey) + MainWindow.Length):
            size = (size << 8) + int.from_bytes(array[i], "big")

        if size > self.data.capacity:
            self.set_output_message("Ошибка декодирования! Размер заголовка превышает размер сообщения.")
            return

        array.clear()
        array = read_bytes(self.image, header, size)

        text = bytes(array).decode("utf-8")

        self.ui.text_edit.setPlainText(text)
        self.set_output_message(f"Присутствует сообщение длиной {size} байт.")

    @Slot()
    def message_changed(self):
        array = QByteArray()
        array.push_back(self.get_input().encode())
        self.data.current = len(array)

        if self.data.less():
            argument = self.data.difference()
            self.set_output_message(f"Ещё можно ввести: {argument} байт.")
            return

        if self.data.maximum():
            self.set_output_message("Размер сообщения достиг максимума.")
            return

        argument = self.data.rdifference()
        self.set_output_message(f"Размер сообщения превышен на: {argument} байт.")

    def set_output_message(self, text):
        self.ui.output_label.setText(text)

