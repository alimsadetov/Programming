#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;





struct Student
{
    string name;
    int group;
    map<string, int> exams;
};






bool kto(Student first, Student second)
{
    return (first.name > second.name);
}


int main()
{
    srand(time(0));
    vector<Student> Students, Loosers;
    Students =
    {
    { "Klounov V",  1, { {"mathematics", 5}, {"physics", 3}, {"history", 5}, {"programming", 5} } },
    { "Nikolaev R",   1, { {"mathematics", 4}, {"physics", 4}, {"history", 5}, {"programming", 3} } },
    { "Russkiy M", 1, { {"mathematics", 2}, {"physics", 2}, {"history", 2}, {"programming", 2} } },
    { "rastislavskiy N",    1, { {"mathematics", 5}, {"physics", 2}, {"history", 3}, {"programming", 4} } },
    { "Rostovskiy V",     2, { {"mathematics", 3}, {"physics", 4}, {"history", 2}, {"programming", 3} } },
    { "Razumov Debil",    3, { {"mathematics", 4}, {"physics", 3}, {"history", 3}, {"programming", 4} } },
    { "Chabanov V",    4, { {"mathematics", 2}, {"physics", 5}, {"history", 2}, {"programming", 3} } },
    { "Lotkov K",      5, { {"mathematics", 3}, {"physics", 5}, {"history", 5}, {"programming", 5} } },
    { "Nedhok L",   6, { {"mathematics", 4}, {"physics", 3}, {"history", 5}, {"programming", 3} } },
    { "Sarguk L",   7, { {"mathematics", 5}, {"physics", 5}, {"history", 3}, {"programming", 5} } }
    };

    ostream& operator<<(ostream & write, vector<Student> Loosers)
         {
    write << "+--------------+-------+------+------+------+------+" << endl
        << "| Name         | Group | Math | Phys | Hist | Prog |" << endl
        << "+--------------+-------+------+------+------+------+" << endl;
    for (auto student : Loosers)
    {
        write << "| " << student.name << setw(15 - student.name.length())
            << "| " << student.group << setw(7)
            << "| " << student.exams["mathematics"] << setw(6)
            << "| " << student.exams["physics"] << setw(6)
            << "| " << student.exams["history"] << setw(6)
            << "| " << student.exams["programming"] << setw(5)
            << "|" << endl
            << "+--------------+-------+------+------+------+------+" << endl;
    }

    return write;
}




    int second = 0;

    for (auto student : Students)
    {
        for (auto mark : student.exams)
        {
            if (mark.second == 2)
            {
                second=second+1;
                Loosers.push_back(student);
                break;
            }
        }
    }

    if (second == 0)
    {
        cout << "Not found";
    }
    else if (second == 1)
    {
     cout << Loosers[0] << endl
          << "Expulsion\n" << endl
          << Loosers[0];
    }
    else
    {
     cout
         << "Expulsion\n" << endl
       << Loosers[rand() % Loosers.size()];
    }
}