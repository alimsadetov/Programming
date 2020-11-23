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