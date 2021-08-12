#include <iostream>


//Первое задание
//===========================================================
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

//Второе задание
//==========================================================

class Car
{
protected:
    std::string company;
    std::string model;

public:
    Car(std::string _company, std::string _model) 
        : company(_company), model(_model)
        {
            std::cout << "Car company: " << company << " Model: " << model << std::endl;
        }

    virtual ~Car()
    {

    }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar(std::string _company, std::string _model)
        : Car(_company, _model)
        {
            std::cout << "PassengerCar company: " << company << " Model: " << model << std::endl;
        }
    virtual ~PassengerCar()
    {

    }
};

class Bus : virtual public Car
{
public:
    Bus(std::string _company, std::string _model)
        : Car(_company, _model)
        {
            std::cout << "Bus company: " << company << " Model: " << model << std::endl;
        }
    virtual ~Bus()
    {

    }
};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan(std::string _company, std::string _model)
        : Car(_company, _model), PassengerCar(_company, _model), Bus(_company, _model)
        {
            std::cout << "Minivan company: " << company << " Model: " << model << std::endl;
        }
    virtual ~Minivan()
    {
        
    }
};

int main()
{
    //Первое задание
    Parallelogram* p = new Parallelogram (5, 5);
    Rectangle* r = new Rectangle (2, 2);
    Square* s = new Square (3);
    Rhombus* rh = new Rhombus (6, 4);
    Circle* c = new Circle (2);
    
    Figure* f = p;
    std::cout << "Parallelogram area: " << f->area() << std::endl;

    f = r;
    std::cout << "Rectangle area: " << f->area() << std::endl;

    f = s;
    std::cout << "Square area: " << f->area() << std::endl;

    f = rh;
    std::cout << "Rhombus area: " << f->area() << std::endl;

    f = c;
    std::cout << "Circle area: " << f->area() << std::endl;
    std::cout << std::endl << "Second task" << std::endl;

    //Второе задание

    Car car("Lada", "Vesta");
    std::cout << std::endl;

    PassengerCar passengerCar("VW", "Polo");
    std::cout << std::endl;

    Bus bus("Man", "325");
    std::cout << std::endl;

    Minivan minivan("VW", "Transporter");

    return 0;
}