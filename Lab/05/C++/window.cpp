#include "window.hpp"
#include "ui_window.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QBitArray>
#include <QFile>
#include <QTextStream>
#include <iostream>

static size_t to_bits(const size_t value)
{
    return value * 8;
}

static void set_bit(QImage& image, const size_t index, const bool value)
{
    size_t pixel = index / 3;

    int x = pixel % image.width();
    int y = pixel / image.width();

    switch (index % 3)
    {
        case 0:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x010000) | (value << 16));
            break;
        case 1:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x000100) | (value << 8));
            break;
        case 2:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x000001) | value);
            break;
    }
}

static bool get_bit(const QImage& image, const size_t index)
{
    size_t pixel = index / 3;

    int x = pixel % image.width();
    int y = pixel / image.width();

    switch (index % 3)
    {
        case 0:
            return (image.pixel(x, y) >> 16) & 1;
        case 1:
            return (image.pixel(x, y) >> 8) & 1;
        case 2:
            return image.pixel(x, y) & 1;
        default:
            throw std::exception();
    }
}

QByteArray read_bytes(const QImage& image, QByteArray& array, size_t start, size_t length)
{
    char buffer = 0;

    for (size_t i = to_bits(start); i < to_bits(start + length); i++)
    {
        buffer = (buffer << 1) | get_bit(image, i);

        if (i % 8 == 7)
        {
            array.push_back(buffer);
            buffer = 0;
        }
    }

    return array;
}

void write_bytes(QImage& image, QByteArray& array, size_t start)
{
    for (size_t i = to_bits(start); i < to_bits(start + array.size()); i++)
    {
        set_bit(image, i, (array[i / 8] >> (7 - i % 8)) & 1);
    }
}

MainWindow::MainWindow() : MainWindow::MainWindow(nullptr)
{
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), window(new Ui::MainWindow)
{
    this->init();
}

MainWindow::~MainWindow()
{
    clear_image();
    delete window;
}

void MainWindow::init()
{
    window->setupUi(this);

    window->output_label->setWordWrap(true);

    connect(window->text_edit, &QPlainTextEdit::textChanged, this, &MainWindow::message_changed);
    connect(window->load_button, &QPushButton::clicked, this, &MainWindow::read_image);
    connect(window->save_button, &QPushButton::clicked, this, &MainWindow::write_image);

    connect(window->encode_button, &QPushButton::clicked, this, &MainWindow::encode_text);
    connect(window->decode_button, &QPushButton::clicked, this, &MainWindow::decode_text);

    reset_state();
}

QByteArray MainWindow::get_input()
{
    return window->text_edit->toPlainText().toUtf8();
}

void MainWindow::clear_image()
{
    if (!image)
    {
        return;
    }

    delete image;
    image = nullptr;
}

void MainWindow::reset_state()
{
    clear_image();
    update_activity_state();
}

void MainWindow::update_activity_state()
{
    const bool active = image;

    this->window->text_edit->setEnabled(active);
    this->window->save_button->setEnabled(active);
    this->window->decode_button->setEnabled(active);
    this->window->encode_button->setEnabled(active);
}

void MainWindow::read_image()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Открыть картинку"), "", tr("Допустимые форматы (*.png)"));

    if (!filepath.size())
    {
        return;
    }

    reset_state();

    if (!QFile::exists(filepath))
    {
        set_output_message("Изображение '%1' не найдено!", &filepath);
        return;
    }

    image = new QImage();
    if (!image->load(filepath))
    {
        set_output_message("Изображение '%1' не загружено!", &filepath);
        clear_image();
        return;
    }

    image->convertTo(QImage::Format_ARGB32);

    data.capacity = (image->width() * image->height() * 3) / 8 - cryptkey.size() - length;

    set_output_message("Изображение успешно загружено");
    update_activity_state();
}

void MainWindow::write_image()
{
    if (!image)
    {
        set_output_message("Изображение не загружено в программу!");
        return;
    }

    QString filepath = QFileDialog::getSaveFileName(this, tr("Сохранить картинку"), "", tr("Допустимые форматы (*.png)"));

    if (image->save(filepath, "PNG"))
    {
        set_output_message("Изображение успешно сохранено в %1", &filepath);
        return;
    }

    set_output_message("Изображение не сохранено");
}

void MainWindow::encode_text()
{
    if (!image)
    {
        set_output_message("Изображение не загружено в программу!");
        return;
    }

    QByteArray input = get_input();
    data.current = input.size();

    if (data.overflow())
    {
        set_output_message("Недостаточно места для кодирования!");
        return;
    }

    QByteArray array;
    array.push_back(cryptkey);
    for (int i = length - 1; i >= 0; i--)
    {
        array.push_back((data.current >> to_bits(i)) & 0xff);
    }

    array.push_back(input);

    write_bytes(*image, array, 0);

    set_output_message("Сообщение добавлено в изображение!");
}

void MainWindow::decode_text()
{
    if (!image)
    {
        set_output_message("Изображение не загружено в программу!");
        return;
    }

    size_t header = cryptkey.size() + length;

    QByteArray array;
    read_bytes(*image, array, 0, header);

    for (size_t i = 0; i < cryptkey.size(); i++)
    {
        if (cryptkey[i] != array[i])
        {
            set_output_message("Сообщение отсутствует!");
            return;
        }
    }

    size_t size = 0;
    for (size_t i = cryptkey.size(); i < cryptkey.size() + length; i++)
    {
        size = (size << 8) + static_cast<unsigned char>(array[i]);
    }

    if (size > data.capacity)
    {
        set_output_message("Ошибка декодирования! Размер заголовка превышает размер сообщения.");
        return;
    }

    array.clear();
    read_bytes(*image, array, header, size);

    QString text = QString::fromUtf8(array);

    window->text_edit->setPlainText(text);

    set_output_message("Присутствует сообщение длиной %1 байт.", &size);
}

void MainWindow::message_changed()
{
    data.current = get_input().size();

    if (data.less())
    {
        size_t argument = data.difference();
        set_output_message("Ещё можно ввести: %1 байт.", &argument);
        return;
    }

    if (data.maximum())
    {
        set_output_message("Размер сообщения достиг максимума.");
        return;
    }

    size_t argument = data.rdifference();
    set_output_message("Размер сообщения превышен на: %1 байт.", &argument);
}

void MainWindow::set_output_message(QString message)
{
    window->output_label->setText(message);
}

template<typename T>
void MainWindow::set_output_message(const char* str, const T* argument)
{
    QString message;
    if (str)
    {
        message = tr(str);
    }

    if (argument)
    {
        window->output_label->setText(message.arg(*argument));
        return;
    }

    window->output_label->setText(message);
}

