<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-201(2)<br>
Садетов Алим Асанович<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

# Лабораторная работа №1 Погода
**Постановка задачи:** Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса. В качестве источника данных о погоде используется: [http://openweathermap.org/](http://openweathermap.org/). В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.

Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису _openweathermap.org_. Сервер должен обеспечивать возможность получения данных в формате JSON.

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

**Цель работы:** 
* Закрепить навыки работы с json
* Закрепить навыки работы с многофайловыми приложениями
* Получить базовое представление о взаимодействии приложений посредством создания клиент-сервеного приложения

## Ход работы

### 1. Получение API Key
Для получения API Key я зарегистрировался на сайте [http://openweathermap.org/](http://openweathermap.org/). После регистрации в разделе API Keys воспользовался пунктом "Create Key" (рис. 1) и сгенерировал бесплатный API-ключ. **Полученный API-ключ**: **e88ae3e431bbe8ed808fd00b5faa66b7**

![](./images/pic1.png)

Рис. 1. Форма создания ключа на сайте openweathermap.org

### 2. Составление запроса для подключения погоды
В ходе лабораторной работы, был изучен формат составления запросов к сервису openweathermap.org. Были изучены примеры работы использования API на официальном сайте сервиса: [http://openweathermap.org/appid#use](http://openweathermap.org/appid#use). Наиболее удобным интерфейсом для нас является One Call API, который позволяет одним вызовом получить данные о погоде для указанного места.


В структуре ответа сервера содержится информация о почасовом прогнозе на 48 часов (рис. 2).

Необходимыми query параметрами для составления запроса являются: 
• lang=ru - язык (По условию нам необходим русский)
• lat - широта (Для Симферополя - 44.952116)
• lon - долгота (Для Симферополя - 34.102411)
• appid - API ключ

![](./images/pic2.png)

Рис. 2. Ответ openweathermap на запрос

Таким образом я составил http-запрос: http://openweathermap.org/data/2.5/onecall?id=524901&lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts&units=metric&lang=ru&appid=9fd2c8de79d6e9abd6cbfc320884918d"

### 3. Составление запроса для получения времени
Для того чтобы получить необходимое время в Симферополе, воспользуемся сервисом [http://worldtimeapi.org/pages/schema](http://worldtimeapi.org/pages/schema). Сервис является бесплатным и не требует регистрации. Изучив примеры использования API с официального сайта, я получил запрос (рис. 4): http://worldtimeapi.org/api/timezone/Europe/Simferopol

![](./images/pic3.png)

Рис. 3. Ответ worldtimeapi на запрос

### 4. Серверное приложение
Для запуска сервера, был использован язык C++, а также сторонние библиотеки: httplib (для работы с HTTP-клиентом и HTTP-сервером), JSON for Modern C++ (позволяет работать с JSON-файлами). Если приходит запрос на "/", сервер формирует и отправляет html-виджет, если же запрос приходит на "/raw", сервер формирует и отправляет json-файл с данными о текущей температуре и состоянии погоды.
Вот исходный [[код сервера]](./c++/server/server.cpp)
<code>
<section>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "include/cpp_httplib/httplib.h"
#include "include/nlohmann/json.hpp"


using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using namespace httplib;

void gen_response(const Request& req, Response& res);
void gen_response_raw(const Request& req, Response& res);

int main()
{
    //создание сервера
    Server weather;
    weather.Get("/", gen_response);
    weather.Get("/raw", gen_response_raw);
    cout << "Start server... OK\n";
    weather.listen("localhost", 3000);
}

//получение json с данными о погоде в симферополе
json GetWeather()
{
    //lat и lon - координаты симферополя, appid - был получен при регистрации на openweathermap
    string req= "/data/2.5/onecall?id=524901&lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts&units=metric&lang=ru&appid=9fd2c8de79d6e9abd6cbfc320884918d";
  
    Client get_weather("http://api.openweathermap.org");
    auto res = get_weather.Get(req.c_str());
    if (res) {
        if (res->status == 200)
        {
            json vivod = res->body;
            return vivod;
        }
        else
        {
            cout << "Status code: " << res->status << endl;
        }
    }
    else//если ошибка
    {
        auto err = res.error();
        cout << "Error code: " << err << endl;
    }
}

//получение времени с worldtimeapi
string GetTime()
{
    Client get_time("http://worldtimeapi.org");
    auto res = get_time.Get("/api/timezone/Europe/Simferopol");
    if (res) {
        if (res->status == 200)
        {
            string result = res->body;
            return result;
        }
        else
        {
            cout << "Status code: " << res->status << endl;
        }
    }
    else
    {
        auto err = res.error();
        cout << "Error code: " << err << "\n";
    }
}

bool file_emptyfier(std::ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

json sozdatel_cache(ifstream& ReadCache)
{
    json RawKash;
    RawKash = GetWeather();
    ofstream wc("kash.json");
    cout << "cache generiruetsya, terpite...\n";
    wc << std::setw(2) << RawKash << "\n";
    return RawKash;
}

//замена в weather.html
string remove_string_in_html(string FToRemove, json cache, int curr_hour)
{
    string r1 = "{hourly[i].weather[0].description}";
    string r2 = "{hourly[i].weather[0].icon}";
    string r3 = "{hourly[i].temp}";

    double tempd = cache["hourly"][curr_hour]["temp"];
    string temps = std::to_string(int(round(tempd)));
    string desk = cache["hourly"][curr_hour]["weather"][0]["description"];
    string icon = cache["hourly"][curr_hour]["weather"][0]["icon"];

    FToRemove.replace(FToRemove.find(r1), r1.length(), desk);
    FToRemove.replace(FToRemove.find(r2), r2.length(), icon);
    FToRemove.replace(FToRemove.find(r3), r3.length(), temps);
    FToRemove.replace(FToRemove.find(r3), r3.length(), temps);
    return FToRemove;
}

int kakoe_vremya(json cache)
{
    int current_hour = 100;
    long unixtime;

    json current_time_full = json::parse(GetTime());
    unixtime = current_time_full["unixtime"];
    for (int i = 0; i < 48; i++)
    {
        long w_unixtime = cache["hourly"][i]["dt"];
        if (unixtime < w_unixtime)
        {
            current_hour = i;
            break;
        }
    }
    return current_hour;
}

json cache_reading(ifstream& rc)
{
    json cache;
    bool not_exist_cache = !rc.is_open() or file_emptyfier(rc);

    if (not_exist_cache)
    {//создать кэш
        cache = sozdatel_cache(rc);
    }
    else
    {
        rc >> cache;
        cout << "Cache reading - OK" << endl;
    }
    return cache;
}

void gen_response_raw(const Request& req, Response& res)
{
    ifstream rc("kash.json");
    json RawCache = cache_reading(rc);
    string temp = RawCache;
    json cache = json::parse(temp);
    int curr_hour = kakoe_vremya(cache);

    if (curr_hour == 100)
    {
        RawCache = sozdatel_cache(rc);
        temp = RawCache;
        cache = json::parse(temp);
    }

    json data;
    double tempd = cache["hourly"][curr_hour]["temp"];
    int tempi = round(tempd);
    string desk = cache["hourly"][curr_hour]["weather"][0]["description"];

    data["temperature"] = tempi;
    data["description"] = desk;
    res.set_content(data.dump(), "text/json");
}

void gen_response(const Request& req, Response& res)
{
    ifstream rc("kash.json");
    json RawCache = cache_reading(rc);
    string temp = RawCache;
    json cache = json::parse(temp);
    int current_hour = kakoe_vremya(cache);

    if (current_hour == 100)
    {
        RawCache = sozdatel_cache(rc);
        temp = RawCache;
        cache = json::parse(temp);
    }

    string vidg;
    ifstream rw("weathersimf.html");  //файловая переменная
    if (rw.is_open())  //проверка открылся файл или нет
    {
        getline(rw, vidg, '\0');
    }
    else
        cout << "Opening - Not OK";

    string vivod = remove_string_in_html(vidg, cache, current_hour);
    res.set_content(vivod, "text/html");
}
</section>
</code>

	

### 5. Клиентское приложение
Создаём клиентское приложение, которое будет посылать запросы на 3000 порт localhost, обрабатывать json файл и отображать погоду на текущий момент. Приложение создаётся на python с использованием библиотеки tkinter. Вот полный исходный [[код клиентского приложения]](./python/python.py)



### 6. Графический интерфейс
Для создания графического интерфейса приложения (рис. 4) использовалась библиотека tkinter.

![](./images/pic4.png)

Рис. 5. Графический интерфейс приложения

### 7. Виджет
При подключении к "/" на сервере, программа автоматически изменяет локальный файл "widget.html" и редактирует соответствующие поля с данными о погоде, затем возвращает браузеру виджет в виде html-документа (рис. 5).

![](./images/pic5.png)

Рис. 5. Виджет

## Вывод

* Были закреплены навыки работы в json
* Были изучены способы работы с api
* Были получены базовые знания о взаимодействии приложений