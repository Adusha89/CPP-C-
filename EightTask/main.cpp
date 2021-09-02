#include <iostream>
#include <array>

const size_t _X = 10;
const size_t _Y = 10;
enum move
{
    FORWARD = 1,
    BACK = 2,
    UP = 3,
    DOWN = 4
};

std::ostream& operator<< (std::ostream& out, const enum move& m)
{
    if (m == 1) 
    {
        return out << "FORWARD";
    }
        if (m == 2) 
    {
        return out << "BACK";
    }
        if (m == 3) 
    {
        return out << "UP";
    }
        return out << "DOWN";
}


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

    const double& getX() const
    {
        return x;
    }

};

std::ostream& operator<< (std::ostream& out, const Ex& ex)
{
    return out << ex.getX();
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

    const double& getY() const
    {
        return y;
    }

};

std::ostream& operator<< (std::ostream& out, const Bar& bar)
{
    return out << bar.getY();
}

class OffTheField
{
private:
    size_t m_current_X;
    size_t m_current_Y;
    move m_move;

public:
    OffTheField(size_t current_X, size_t current_Y, move move) :
        m_current_X(current_X), m_current_Y(current_Y), m_move(move)
    {

    }

    const size_t& get_X() const
    {
        return m_current_X;
    }
    
    const size_t& get_Y() const
    {
        return m_current_Y;
    }

    const move& get_Move() const
    {
        return m_move;
    }
};

std::ostream& operator<< (std::ostream& out, const OffTheField& otf)
{
    return out << "Current position is X(" << otf.get_X() << ")Y("
        << otf.get_Y() << "), MOVE - (" << otf.get_Move() << 
            ") is OUT OF THE FIELD!"; 
}

class IllegalCommand
{
private:
    size_t m_current_X;
    size_t m_current_Y;
    int m_move;

public: 
    IllegalCommand(size_t current_X, size_t current_Y, int move) :
        m_current_X(current_X), m_current_Y(current_Y), m_move(move)
    {

    }
        const size_t& get_X() const
    {
        return m_current_X;
    }
    
    const size_t& get_Y() const
    {
        return m_current_Y;
    }

    const int& get_Move() const
    {
        return m_move;
    }
};

std::ostream& operator<< (std::ostream& out, const IllegalCommand& ill)
{
    return out << "Current position is X(" << ill.get_X() << ")Y("
        << ill.get_Y() << "), MOVE - (" << ill.get_Move() << 
            ") is ILLEGAL COMMAND!"; 
}

class Robot
{
private:
    std::array<std::array<char, _Y>, _X> m_field;
    size_t m_currentX;
    size_t m_currentY;
    char m_robot;


public:
    Robot() : m_robot('R'), m_currentX(0), m_currentY(0)
    {
        for (auto& fieldRow : m_field)
        {
            for (auto& elFieldRow : fieldRow)
            {
                elFieldRow = '.';
            }
        }

        m_field[0][0] = m_robot;
    }

    const std::array<std::array<char, _Y>, _X>& getm_Field() const
    {
        return m_field;
    }

    void go(int move)
    {
        if (!(move == FORWARD || move == BACK || move == UP || move == DOWN))
        {
            throw IllegalCommand(m_currentX, m_currentY, move);
        }

        switch (move)
        {
        case FORWARD:
            if (m_currentY + 1 == 10)
            {
                throw OffTheField(m_currentX, m_currentY, static_cast<enum::move>(move));
            }

            m_field[m_currentX][m_currentY] = '.';
            m_field[m_currentX][++m_currentY] = m_robot;
            break;
        
        case BACK:
            if (static_cast<int>(m_currentY) - 1 < 0)
            {
                throw OffTheField(m_currentX, m_currentY, static_cast<enum::move>(move));
            }
            m_field[m_currentX][m_currentY] = '.';
            m_field[m_currentX][--m_currentY] = m_robot;
            break;
        
        case DOWN:
            if (m_currentX + 1 == 10)
            {
                throw OffTheField(m_currentX, m_currentY, static_cast<enum::move>(move));
            }
            m_field[m_currentX][m_currentY] = '.';
            m_field[++m_currentX][m_currentY] = m_robot;
            break;
        
        case UP:
            if (static_cast<int>(m_currentX) - 1 < 0)
            {
                throw OffTheField(m_currentX, m_currentY, static_cast<enum::move>(move));
            }
            m_field[m_currentX][m_currentY] = '.';
            m_field[--m_currentX][m_currentY] = m_robot;
            break;
        
        }
    }
};

std::ostream& operator<< (std::ostream& out, const Robot& r)
{
    for (auto& fieldRow : r.getm_Field())
    {
        for (auto& elFieldRow : fieldRow)
        {
            out << elFieldRow;
        }
        std::cout << std::endl;
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
    int step;
    std::cout << r << std::endl;

    while (true)
    {
        
        std::cout << "Where are we going?" << std::endl
            << " 1 - Forward\n 2 - Back\n 3 - Up\n 4 - Down\n 0 - Exit" << std::endl;
        
        std::cin >> step;
        if (!step)
        {
            break;
        }

        try
        {
            r.go(step);
            std::cout << r << std::endl;
        }
        catch(const OffTheField& errOff)
        {
            std::cerr << errOff << std::endl;
        }
        catch(const IllegalCommand& errIll)
        {
            std::cerr << errIll << std::endl;
        }

    }
    
    
    
    return 0;
}
