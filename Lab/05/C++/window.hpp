#pragma once

#include <QMainWindow>
#include <array>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

struct cryptdata
{
    size_t current = 0;
    size_t capacity = 0;

    bool less();
    bool overflow();
    bool maximum();

    size_t difference();
    size_t rdifference();
};

class MainWindow : public QMainWindow
{
private:
    Q_OBJECT

    QByteArray get_input();
    void set_output_message(QString msg);
    template<typename T>
    void set_output_message(const char* str, const T* argument = nullptr);
    void init();
    void clear_image();
    void reset_state();
    void update_activity_state();

    Ui::MainWindow* window;
    QImage* image = nullptr;
    cryptdata data;

    const std::array<char, 3> cryptkey
    {
        static_cast<char>(0b11100010),
        static_cast<char>(0b10011101),
        static_cast<char>(0b10100100)
    };

    static constexpr size_t length = 4;

public:
    MainWindow();
    MainWindow(QWidget* parent);
    ~MainWindow();

public slots:
    void read_image();
    void write_image();
    void encode_text();
    void decode_text();
    void message_changed();
};
