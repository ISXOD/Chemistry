#include <iostream>
#include <string>
#include <Windows.h>
#include<fstream>

using namespace std;

const int COUNT_ANION = 1;
const int COUNT_CATION = 3;
class Ion
{
public:
    string name;
    int charge;
    enum type_ion { CATION, ANION };
    type_ion type;
    Ion(string name, int charge)
    {
        this->charge = charge;
        this->name = name;
        if (charge > 0)
        {
            type = type_ion::CATION;
        }
        else
        {
            type = type_ion::ANION;
        }
    }
    Ion()
    {

    }
    void Print(ofstream& fout)
    {
        fout << name <<" "<< charge <<" "<< this->type << endl;
    }
};
Ion cation[COUNT_CATION]{ Ion("LI",1), Ion("Fe",3), Ion("Cl", 1) };
Ion anion[COUNT_ANION]{ Ion("O", -2) };
class Element
{
public:
    enum type { OXIDE_O, OXIDE_A, OXIDE_K };
    type type_element;
    string name;
    Ion cation_e, anion_e;
    void Print(ofstream & fout)
    {
        fout << name << " " << this->type_element;
    }
    Element()
    {

    }
};
Element Sum_Ion(const Ion first, const Ion second)
{
    Element element;
    int count_anion = 1, count_cation = 1, num_anion_in_mass, num_cation_in_mass;
    int count = first.charge + second.charge;
    while (count != 0)
    {
        if (count > 0)
        {
            count += second.charge;
            count_anion++;
        }
        else
        {
            count += first.charge;
            count_cation++;
        }
    }
    if (count_anion == 1)
    {
        element.name = first.name + to_string(count_cation) + second.name;
    }
    else if (count_cation == 1)
    {
        element.name = first.name + second.name + to_string(count_anion);
    }
    else 
    {
        element.name = first.name + to_string(count_cation) + second.name + to_string(count_anion);
    }
    element.anion_e = second;
    element.cation_e = first;
    for (int i = 0; i < COUNT_ANION; i++)
    {
        if (second.name == anion[i].name)
        {
            num_anion_in_mass = i;
        }
    }
    for (int i = 0; i < COUNT_CATION; i++)
    {
        if (first.name == cation[i].name)
        {
            num_cation_in_mass = i;
        }
    }
    if (num_anion_in_mass == 0)
    {
        if (num_cation_in_mass == 0)
        {
            element.type_element = element.type::OXIDE_O;
        }
        else if (num_cation_in_mass == 1)
        {
            element.type_element = element.type::OXIDE_A;
        }
        if (num_cation_in_mass == 2)
        {
            element.type_element = element.type::OXIDE_K;
        }
    }
    return element;
}
int main()
{
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
    Element mass[3][1];
    for (int i = 0; i < COUNT_ANION; i++)
    {
        for (int j = 0; j < COUNT_CATION; j++)
        {
            mass[j][i] = Sum_Ion(cation[j], anion[i]);
        }
    }
    // Создание БД в виде txt файла
    ifstream fout;
    fout.open("DataSet.txt");
    // Проверка
    if (!fout.is_open())
    {
        cout << "Что-то пошло не так..." << endl;
    }
    else
    {
        fout << COUNT_ANION << endl;
        for (int i = 0; i < COUNT_ANION; i++)
        {
            anion[i].Print(fout);
        }
        fout << COUNT_CATION << endl;
        for (int i = 0; i < COUNT_CATION; i++)
        {
            cation[i].Print(fout);
        }

        fout << COUNT_CATION * COUNT_ANION << endl;
        for (int i = 0; i < COUNT_CATION; i++)
        {
            for (int j = 0; j < COUNT_ANION; j++)
            {
                mass[j][i].Print(fout);
            }
            fout << endl;
        }
        fout.close();
    }
    return 0;
}