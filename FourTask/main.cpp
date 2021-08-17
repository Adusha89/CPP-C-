#include <iostream>
#include <cassert>
#include <vector>

class ArrayInt
{
private:
    size_t m_lenght;
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
            for (size_t idx = 0; idx < lenght; ++idx)
            {
                m_data[idx] = 0;
            }
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

    size_t getLenght() const
    {
        return m_lenght;
    }

    int& operator[](int index)
    {
        assert(index >= 0 || index < m_lenght);
        return m_data[index];
    }

    void resize(int newlenght)
    {
        if (m_lenght == newlenght)
        {
            return;
        }

        if (newlenght <= 0)
        {
            erase();
            return;
        }

        int* data = new int [newlenght];

        int elementsToCopy = (newlenght > m_lenght) ? m_lenght : newlenght;
        for (size_t idx = 0; idx < elementsToCopy; ++idx)
        {
            data[idx] = m_data[idx];
        }

        if (elementsToCopy < newlenght)
        {
            for (size_t idx = elementsToCopy; idx < newlenght; ++idx)
            {
                data[idx] = 0;
            }
        }

        delete[] m_data;
        m_data = data;
        m_lenght = newlenght;

    }

    

    void print() const
    {
        if (!m_lenght)
        {
            std::cout << "Array is empty!" << std::endl;
            return;
        }

        for (size_t idx = 0; idx < m_lenght; ++idx)
        {
            std::cout << m_data[idx] << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    ArrayInt array(5);
    array.print();
    array.resize(7);
    array.print();

    return 0;
}
