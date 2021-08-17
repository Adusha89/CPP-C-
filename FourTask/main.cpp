#include <iostream>
#include <cassert>
#include <vector>

class ArrayInt
{
private:
    size_t m_lenght; //Длина массива фактическая, кол-во элементов
    size_t m_size; //Размер выделяемой памяти
    int* m_data;

public:
    ArrayInt() : m_lenght(0), m_size(0), m_data(nullptr)
    {

    }

    ArrayInt(int size) : m_lenght(0), m_size(size)
    {
        assert(size >= 0);

        if(size > 0)
        {
            m_data = new int (size);
            for (size_t idx = 0; idx < size; ++idx)
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
        m_size = 0;
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

    void resize(int newsize)
    {
        if (m_size == newsize)
        {
            return;
        }

        if (newsize <= 0)
        {
            erase();
            return;
        }

        int* data = new int [newsize];

        int elementsToCopy = (newsize > m_lenght) ? m_lenght : newsize;
        for (size_t idx = 0; idx < elementsToCopy; ++idx)
        {
            data[idx] = m_data[idx];
        }

        if (elementsToCopy < newsize)
        {
            for (size_t idx = elementsToCopy; idx < newsize; ++idx)
            {
                data[idx] = 0;
            }
        }

        delete[] m_data;
        m_data = data;
        m_lenght = elementsToCopy;
        m_size = newsize;

    }

    //Перегрузка метода, по-умолчанию, увеличивает память в два раза
    //Нужно для push
    void resize()
    {

        int* data = new int [m_size * 2];

        for (size_t idx = 0; idx < m_lenght; ++idx)
        {
            data[idx] = m_data[idx];
        }

        for (size_t idx = m_lenght; idx < m_size * 2; ++idx)
        {
            data[idx] = 0;
        }

        delete[] m_data;
        m_data = data;
        m_size *= 2;
    }

    void pop_back()
    {
        //Т.к. алоцирование памяти дорогостоящая операция, то решил не перевыделять
        --m_lenght;
    }

    void pop_front()
    {
        for (size_t idx = 0; idx < m_lenght - 1; ++idx)
        {
            m_data[idx] = m_data[idx+1];
        }
        --m_lenght;
    }

    void push_back(int element)
    {
        if (!m_size) 
        {
            resize(1);
        }
        if (m_lenght > m_size)
        {
            resize();
        }
        m_data[m_lenght++] = element;
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
    array.push_back(4);
    array.push_back(4);
    array.pop_back();
    array.push_back(4);
    array.pop_front();
    array.print();
    std:: cout << array.getLenght() << std::endl;
   
    return 0;
}
