#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

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
        ace = 11
    } m_nominal;

    bool m_isFaceUp = false; //рубашкой вверх

public:

    Card(uint8_t suit, uint8_t nominal, bool is_FaceUp = false)
        : m_suit(static_cast<Suit>(suit)), m_nominal(static_cast<Nominal>(nominal)), m_isFaceUp(is_FaceUp)
    {

    }

    virtual ~Card()
    {

    }

    void Flip()
    {
        m_isFaceUp = !m_isFaceUp;
    }

    uint8_t GetValue() const
    {
        if(m_isFaceUp)
        {
            return static_cast<uint8_t>(m_nominal);
        }
        return 0;
        
    }

};

class Hand
{
private:
    std::vector<Card*> m_Cards;

public:

    virtual ~Hand()
    {
        Clear();
    }

    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }

    void Clear()
    {
        for (uint8_t idx = 0; idx < m_Cards.size(); ++idx)
        {
            delete m_Cards[idx];
        }
        m_Cards.clear();
    }

    uint8_t GetTotal() const
    {
        uint8_t sum = 0;
        uint8_t card;

        if (m_Cards.empty())
        {
            return 0;
        }

        if (m_Cards[0]->GetValue() == 0)
        {
            return 0;
        }

        for (uint8_t idx = 0; idx < m_Cards.size(); ++idx)
        {
            card = m_Cards[idx]->GetValue();
            if(card == 11 && sum + card > 21)
            {
                sum = card + sum - 10;
            }
            else
            {
                sum += card;
            }
        }
        return sum;
    }

};

class ArrayInt
{
private:
    size_t m_lenght; //Длина массива, Размер выделяемой памяти
    size_t m_count; //Кол-во элементов
    int* m_data;

public:
    ArrayInt() : m_lenght(0), m_count(0), m_data(nullptr)
    {

    }

    ArrayInt(int lenght) : m_lenght(lenght), m_count(0)
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
        m_count = 0;
    }

    size_t getLenght() const
    {
        return m_lenght;
    }

    int& operator[](int index)
    {
        assert(index >= 0 || index < m_count);
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

        size_t elementsToCopy = (newlenght > m_count) ? m_count : newlenght;
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
        m_count = elementsToCopy;
        m_lenght = newlenght;

    }

    void pop_back()
    {
        if(!m_count)
        {
            std::cout << "Array is empty" << std::endl;
        }
        else
        {
            //Т.к. алоцирование памяти дорогостоящая операция, то решил не перевыделять
            --m_count;
        }
        
    }

    void pop_front()
    {
        if(!m_count)
        {
            std::cout << "Array is empty" << std::endl;
        }
        else
        {
            for (size_t idx = 0; idx < m_count - 1; ++idx)
            {
                m_data[idx] = m_data[idx+1];
            }
                --m_count;
        }
        
    }

    void push_back(int element)
    {
        if (!m_lenght) 
        {
            resize(1);
        }
        if (m_count + 1 > m_lenght)
        {
            resize(m_lenght*2);
        }
        m_data[m_count++] = element;
    }

    void sort()
    {
        int swap;

        if(!m_count)
        {
            std::cout << "Array is empty!" << std::endl;
            return;
        }
        for (size_t idx = 0; idx < m_count; ++idx)
        {
            for (size_t idx_j = 1; idx_j < m_count - idx; ++idx_j)
            {
                if (m_data[idx_j] < m_data[idx_j-1])
                {
                    swap = m_data[idx_j];
                    m_data[idx_j] = m_data[idx_j-1];
                    m_data[idx_j-1] = swap;

                }
            }
        }
    }

    void print() const
    {
        if (!m_count)
        {
            std::cout << "Array is empty!" << std::endl;
            return;
        }

        for (size_t idx = 0; idx < m_count; ++idx)
        {
            std::cout << m_data[idx] << " ";
        }
        std::cout << std::endl;
    }
};

void secondTask()
{
    std::cout <<std::endl << "Second task" << std::endl;
    std::vector<int> arr{1, 3, 6, 4, 4, 1, 6, 7};
    std::sort(arr.begin(), arr.end());
    size_t count = 0;

    if(arr.size())
    {   
        ++count;
        for (size_t idx = 0; idx < arr.size() - 1; ++idx)
        {
            if (arr[idx+1] != arr[idx])
            {
                ++count;
            }
        }
        std::cout << count << std::endl;
    }
    else
    {
        std::cout << "Vector is empty" << std::endl;
    }
    
}

int main(int argc, char const *argv[])
{
    ArrayInt array(5);
    array.print();
    array.pop_front();
    array.push_back(5);
    array.print();
    array.push_back(4);
    array.push_back(3);
    array.push_back(2);
    array.push_back(1);
    array.push_back(1);
    array.push_back(3);
    array.push_back(2);
    array.print();
    array.pop_front();
    array.pop_back();
    array.push_back(2);
    array.push_back(1);
    array.print();
    array.sort();
    array.print();


    secondTask();

    Hand h;
    h.Add(new Card(2, 11, true));
    h.Add(new Card(2, 11, true));
    h.Add(new Card(2, 8));

    std::cout << "Third Task" << std::endl;
    std::cout << +h.GetTotal() << std::endl;

    return 0;
}
