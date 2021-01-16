#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


enum ItemType
{
    COIN,
    RUNE,
    WEAPON,
    ARMOR
};



//дальше вниз идут много структур
struct Coin
{
    int count;
};




enum Element
{
    FIRE,
    WATER,
    EARTH,
    AIR
};




struct Rune
{
    int level;
    Element element;
};



struct Weapon
{
    int damage;
    int critical;
    int durability;
};




struct Armor
{
    int guard;
    int durability;
};



//структ айтем
struct Item
{
    ItemType type;
    union {
        Coin coin;
        Rune rune;
        Weapon weapon;
        Armor armor;
    } item;
};

ostream& operator << (ostream& out, Item item)
{
    string name;
    switch (item.type)
    {
    case COIN:
        name = "1000 zoloto";
        break;
    case RUNE:
        name = "Rune of element";
        switch (item.item.rune.element)
        {
        case FIRE:
            name += "fire";
            break;
        case EARTH:
            name += "earth";
            break;
        case WATER:
            name += "water";
            break;
        case AIR:
            name += "vozduh";
            break;
        }
        name += " " +to_string(item.item.rune.level) + " lvl";
        break;
    case WEAPON:
        if (item.item.weapon.critical == 0)
        {
            name = "god killer";
        }
        else if (item.item.weapon.critical == 50)
        {
            name = "demon slayer";
        }
        break;
    case ARMOR:
        name = "bronezhiletka";
        break;
    }

    return out << name;
}

//здесь ещё должна быть функция потом допилю




















int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    while (1)
    {
        string otvet;
        cout << "Открыть лут? Yes/No" << endl;
        cin >> otvet;
        if (otvet == "Y" or otvet == "Yes" or otvet == "y" or otvet == "yes")
        {
            ;
        }
        else if (otvet == "N" or otvet == "No" or otvet == "n" or otvet == "no")
        {
            break;
        }
        else
        {
            continue;
        }
    }
}