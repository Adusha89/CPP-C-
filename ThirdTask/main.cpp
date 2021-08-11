#include <iostream>


//Первое задание
class Figure
{
public:

    Figure()
    {

    }

    virtual ~Figure()
    {

    }
    virtual double area() const = 0;

};

class Parallelogram : public Figure
{
protected:
    double m_lenght;
    double m_height;

public:
    Parallelogram(double _lenght, double _height)
        : m_lenght(_lenght), m_height(_height)
    {

    }

    virtual ~Parallelogram()
    {

    }

    double area() const override
    {
        return m_lenght * m_height;
    }
};

class Rectangle : public Parallelogram
{
public:
    Rectangle(double _lenght, double _height)
        : Parallelogram(_lenght, _height)
    {

    }   

    virtual ~Rectangle()
    {

    } 

    double area() const override
    {
        return m_lenght * m_height;
    }
};

class Square : public Parallelogram
{
public:
    Square(double _lenght)
        : Parallelogram(_lenght, _lenght)
    {

    }   

    virtual ~Square()
    {

    } 

    double area() const override
    {
        return m_lenght * m_lenght;
    }
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(double _lenght, double _height)
        : Parallelogram(_lenght, _height)
    {

    }   

    virtual ~Rhombus()
    {

    } 

    double area() const override
    {
        return m_lenght * m_height;
    }
};

class Circle : public Figure
{
private:
    double m_radius;
    const double pi = 3.14;

public:
    Circle(double _radius)
        : m_radius(_radius)
    {

    }

    virtual ~Circle()
    {

    }

    double area() const override
    {
        return pi * m_radius * m_radius;
    }

};

int main()
{
    Parallelogram* p = new Parallelogram (5, 5);
    Rectangle* r = new Rectangle (2, 2);
    Square* s = new Square (3);
    Rhombus* rh = new Rhombus (6, 4);
    Circle* c = new Circle (2);
    
    Figure* f = p;
    std::cout << f->area() << std::endl;

    f = r;
    std::cout << f->area() << std::endl;

    f = s;
    std::cout << f->area() << std::endl;

    f = rh;
    std::cout << f->area() << std::endl;

    f = c;
    std::cout << f->area() << std::endl;


    return 0;
}