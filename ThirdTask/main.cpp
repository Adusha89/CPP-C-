#include <iostream>
#include <cstdint>


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

//Третье задание

class Fraction
{
private:

    int m_numerator;
    uint8_t m_denominator;

public:
    Fraction() : m_numerator(0), m_denominator(0)
    {

    }

    Fraction(int numerator, uint8_t denominator)
        : m_numerator(numerator)
    {
        if (denominator == 0)
        {
            //Т.к. не работали с исключенииями, то считаю, что, по умолчанию, если знаменатель равен 0, 
            //то пользователь подразумевал его отсутствие, т.е. 3/0 тождественно целому 3 или 3/1
            m_denominator = 1;
        }
        else 
        {
            m_denominator = denominator;
        }
        
    }


    friend std::ostream& operator<< (std::ostream &out, const Fraction &f1);
    friend Fraction operator+(const Fraction&, const Fraction&);
    friend Fraction operator-(const Fraction&, const Fraction&);
    friend Fraction operator*(const Fraction&, const Fraction&);
    friend Fraction operator/(const Fraction&, const Fraction&);
    friend bool operator==(const Fraction&, const Fraction&);
    friend bool operator!=(const Fraction&, const Fraction&);
    friend bool operator<(const Fraction&, const Fraction&);
    friend bool operator>=(const Fraction&, const Fraction&);
    friend bool operator>(const Fraction&, const Fraction&);
    friend bool operator<=(const Fraction&, const Fraction&);

    Fraction operator-() const
    {
        return Fraction(-m_numerator, m_denominator);
    }

};

std::ostream& operator<< (std::ostream &out, const Fraction &f1)
{
    out << f1.m_numerator << "/" << +f1.m_denominator;
    return out;
}

Fraction operator+(const Fraction& f1, const Fraction& f2)
{   
    if (f1.m_denominator == f2.m_denominator)
    {
        return Fraction((f1.m_numerator + f2.m_numerator), f1.m_denominator);
    }
    return Fraction((f1.m_numerator * f2.m_denominator) + (f2.m_numerator * f1.m_denominator), f1.m_denominator * f2.m_denominator);

}

Fraction operator-(const Fraction& f1, const Fraction& f2)
{   
    if (f1.m_denominator == f2.m_denominator)
    {
        return Fraction((f1.m_numerator - f2.m_numerator), f1.m_denominator);
    }
    return Fraction((f1.m_numerator * f2.m_denominator) - (f2.m_numerator * f1.m_denominator), f1.m_denominator * f2.m_denominator);

}

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    if(f1.m_numerator == 0 || f2.m_numerator == 0) return Fraction();
    return Fraction(f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator);
}

Fraction operator/(const Fraction& f1, const Fraction& f2)
{
    if(f1.m_numerator == 0 || f2.m_numerator == 0) return Fraction();
    return Fraction(f1.m_numerator * f2.m_denominator, f1.m_denominator * f2.m_numerator);
}

bool operator==(const Fraction& f1, const Fraction& f2)
{
    return f1.m_numerator * f2.m_denominator == f2.m_numerator * f1.m_denominator;
}

bool operator!=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 == f2);
}

bool operator<(const Fraction& f1, const Fraction& f2)
{
    return f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator;
}

bool operator>=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 < f2);
}

bool operator>(const Fraction& f1, const Fraction& f2)
{
    return f1.m_numerator * f2.m_denominator > f2.m_numerator * f1.m_denominator;
}

bool operator<=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 > f2);
}

//Четвертое задание
//==========================================================

class Card
{
private:

    enum class Suit //Масть
    {
        spades, //пики
        hearts, //червы
        clubs, //трефы
        diamonds //бубны
    } m_suit;

    enum class Nominal
    {
        two = 2,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack = 10,
        queen = 10,
        king = 10,
        ace = 1
    } m_nominal;

    bool m_isInverted = false; //рубашкой вверх

public:

    Card(uint8_t suit, uint8_t nominal, bool is_inverted = false)
        : m_suit(static_cast<Suit>(suit)), m_nominal(static_cast<Nominal>(nominal)), m_isInverted(is_inverted)
    {

    }

    virtual ~Card()
    {

    }

    void Flip()
    {
        (m_isInverted) ? (m_isInverted = false) : (m_isInverted = true);
    }

    uint8_t GetValue() const
    {
        return static_cast<uint8_t>(m_nominal);
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

    //Четвертое задание
    Card card(3,3);

    std::cout << +card.GetValue() << std::endl;

    //Третье задание
    Fraction a(1, 2);
    Fraction b(1, 2);
    Fraction d(2, 3);

    std::cout << a - (-b) << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;
    std::cout << -d << std::endl;

    std::cout << std::boolalpha << (a == b) << std::endl;
    std::cout << std::boolalpha << (a != b) << std::endl;
    std::cout << std::boolalpha << (a < b) << std::endl;
    std::cout << std::boolalpha << (a >= b) << std::endl;
    std::cout << std::boolalpha << (a > b) << std::endl;
    std::cout << std::boolalpha << (a <= b) << std::endl;

    return 0;
}