#include <iostream>
#include <vector>

// Первое задание
int counter = 0;


class Person
{
private:
    std::string m_name;
    int m_age ;
    std::string m_sex;
    int m_weight;

public:
    Person()
    {
        std::cout << "Input Name: ";
        std::cin >> m_name;

        std::cout << "Input Age: ";
        std::cin >> m_age;

        std::cout << "Input Sex: ";
        std::cin >> m_sex;

        std::cout << "Input Weight: ";
        std::cin >> m_weight;
    }


    void changeName ()
    {
        std::cout << "Change new Name: ";
        std::cin >> m_name;
    }

    void changeAge ()
    {
        std::cout << "Change new Age: ";
        std::cin >> m_age;
    }

    void changeWeight ()
    {
        std::cout << "Change new Weight: ";
        std::cin >> m_weight;
    }

    std::string getName () const
    {
        return m_name;
    }

    int getAge () const
    {
        return m_age;
    }

    std::string getSex () const
    {
        return m_sex;
    }

    int getWeight () const
    {
        return m_weight;
    }
};

class Student : public Person
{
private:
    int m_yearstudy;

public:
    Student ()
    {
        std::cout << "Input year of study: ";
        std::cin >> m_yearstudy;
    }

    int getYearStudy () const
    {
        return m_yearstudy;
    }

    void changeYearStudy ()
    {
        std::cout << "Input new year of study: ";
        std::cin >> m_yearstudy;
    }

    void increaseYearStudy ()
    {
        m_yearstudy++;
    }

    void print() const
    {
        std::cout << std::endl << "Info Student" << std::endl << "Name: " << getName() << std::endl 
            << "Age: " << getAge() << std::endl << "Sex: " << getSex() 
                << std::endl << "Weight: " << getWeight() << std::endl << "Year of Study: " << getYearStudy() << std::endl;
    }


};

using listStudent = std::vector<Student>;

int findStudent (const listStudent &list)
{
    std::string key;
    std::cout << "Input key find" << std::endl;
    std::cin >> key;

    for (size_t i = 0; i < counter; i++)
    {
        if (list[i].getName() == key)
        {
            return i;
        }
    }

    return -1;
}

void editStudent (Student &student)
{
    int choice;

    while (true)
    {   
        std::cout << std::endl;
        std::cout << "Input your choice\n1. Change name\n2. Change age\n3. Change weight\n4. Change year of study\n5. Increase year of study\n0. Exit\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            student.changeName();
            break;

        case 2:
            student.changeAge();
            break;
        
        case 3:
            student.changeWeight();
            break;

        case 4:
            student.changeYearStudy();
            break;

        case 5:
            student.increaseYearStudy();
            break;

        case 0:
            return;

        default:
            std::cout << "Incorrect choice. Try yet" << std::endl;
            break;
        }
    }
}

void firstTask (listStudent &list)
{
    
    int choice;

    while (true)
    {
        std::cout << "Input your choice\n1. Create new student\n2. Find student (by name)\n0. Exit\n";
        
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            list.resize(++counter);
            break;

        case 2:
            if (!counter) std::cout << "List is empty!" << std::endl;
            else 
            {
                int index = findStudent(list);
                if (index >= 0)
                {
                    std::cout << "Student found:" <<std::endl;
                    list[index].print();
                    editStudent(list[index]);
                }
                else std::cout << "Student not found" << std::endl;
            }
            break;

        case 0:
            return;

        default:
            std::cout << "Incorrect choice. Try yet" << std::endl;
            break;
        
        }
        std::cout << std::endl;
    }
}

//Второе задание

class Fruit
{
private:
    std::string m_name;
    std::string m_color;

public:
 
    Fruit(std::string name, std::string color) : m_name(name), m_color(color)
    {

    }

    std::string getName () const
    {
        return m_name;
    }

    std::string getColor () const
    {
        return m_color;
    }

};

class Apple : public Fruit
{
public:
    Apple(std::string name, std::string color) : Fruit(name, color)
    {

    }
    Apple(std::string color) : Fruit("apple", color)
    {

    }
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("banana", "yellow")
    {
        
        
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("Granny Smith apple", "green")
    {

    }
};

int main ()
{
    listStudent list(counter);

    firstTask(list);

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    
    return 0;
}