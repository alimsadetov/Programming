from PySide6.QtCore import QByteArray
from PySide6.QtGui import QImage


def to_bits(value) -> int:
    return value * 8


def set_bit(image: QImage, index, value) -> None:
    pixel = index // 3

    x = pixel % image.width()
    y = pixel // image.width()

    px = index % 3

    if px == 0:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x010000) | (value << 16))
    elif px == 1:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000100) | (value << 8))
    elif px == 2:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000001) | value)


def get_bit(image: QImage, index) -> bool:
    pixel = index // 3

    x = pixel % image.width()
    y = pixel // image.width()

    px = index % 3

    if px == 0:
        return (image.pixel(x, y) >> 16) & 1
    elif px == 1:
        return (image.pixel(x, y) >> 8) & 1
    elif px == 2:
        return image.pixel(x, y) & 1
    else:
        raise Exception()


def read_bytes(image: QImage, start, length) -> QByteArray:
    array = QByteArray()
    buffer = 0

    for i in range(to_bits(start), to_bits(start + length)):
        buffer = (buffer << 1) | get_bit(image, i)

        if i % 8 == 7:
            array.push_back(bytes((buffer,)))
            buffer = 0

    return array


def write_bytes(image: QImage, array: QByteArray, start) -> None:
    for i in range(to_bits(start), to_bits(start + array.size())):
        set_bit(image, i, (int.from_bytes(array[i // 8], "big") >> (7 - i % 8)) & 1)

