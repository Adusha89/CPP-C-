#include <iostream>
#include <cassert>
#include <vector>

class ArrayInt
{
private:
    int m_lenght;
    int* m_data;

public:
    ArrayInt() : m_lenght(0), m_data(nullptr)
    {

    }

    ArrayInt(int lenght) : m_lenght(lenght)
    {
        assert(lenght >= 0);

        if(lenght > 0)
        {
            m_data = new int (lenght);
        }
        else
        {
            m_data = nullptr;
        }
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_lenght = 0;
    }

    int getLenght() const
    {
        return m_lenght;
    }

    int& operator[](int index)
    {
        assert(index >= 0 || index < m_lenght);
        return m_data[index];
    }
};

int main(int argc, char const *argv[])
{
    ArrayInt array(3);
    return 0;
}
