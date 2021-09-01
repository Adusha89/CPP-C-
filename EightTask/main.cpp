#include <iostream>
#include <array>

template<class T>
double div(T div1, T div2)
{
    if (div2 == 0)
    {
        throw "DivisionByZero";
    }
    return static_cast<double>(div1)/static_cast<double>(div2);
}


class Ex
{
private:
    double x;

public:
    Ex(double _x) : x(_x)
    {

    }

    friend std::ostream& operator<< (std::ostream& out, const Ex& ex);
};

std::ostream& operator<< (std::ostream& out, const Ex& ex)
{
    return out << ex.x;
}

class Bar
{
private:
    double y;

public:
    Bar() : y(0)
    {

    }

    void set(const double& a)
    {
        if (y + a > 100)
        {
            throw Ex(y*a);
        }
        else y = a;
    }

    friend std::ostream& operator<< (std::ostream& out, const Bar& bar);
};

std::ostream& operator<< (std::ostream& out, const Bar& bar)
{
    return out << bar.y;
}

class Robot
{
private:
    std::array<char, 100> m_field;
    size_t m_currentX;
    size_t m_currentY;
    char m_robot;


public:
    Robot() : m_robot('R'), m_currentX(0), m_currentY(0)
    {
        for (auto &field : m_field)
        {
            field = '.';
        }
        m_field[0] = m_robot;
    }

    const std::array<char, 100>& getm_Field()
    {
        return m_field;
    }

    void go(size_t x, size_t y)
    {
        
    }
};

std::ostream& operator<< (std::ostream& out, Robot& r)
{
    for (size_t idx = 0; idx < 100; ++idx)
    {
       out << r.getm_Field()[idx];
       if (idx%10 == 9)
       {
           out << "\n";
       }
    }

    return out;
}

int main(int argc, char const *argv[])
{
    try
    {  
       std::cout << div<int>(5,0) << std::endl;
    }
    catch(const char* err)
    {
        std::cout << err << std::endl;
    }

    Bar bar;
    int n;
        do
        {   
            try
            {
                std::cout << "Input n: ";
                std::cin >> n;
                bar.set(static_cast<double>(n));
            }
            catch(const Ex& err)
            {
                std::cout << "Error: " << err << std::endl;
            }
        } while (n);
    
    
    Robot r;
    
    std::cout << r << std::endl;
    
    return 0;
}
