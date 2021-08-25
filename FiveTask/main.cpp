#include <iostream>
#include <vector>

class IInteractive
{
public:
    virtual ~IInteractive()
    {

    }
    virtual void message(const std::string&) const = 0;
};

class Interactive : public IInteractive
{
public:

    virtual ~Interactive()
    {

    }

    void message(const std::string& message) const override
    {
        std::cout << message << std::endl;
    }
};

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

class GenericPlayer : public Hand
{
private:
    std::string name;
    IInteractive* m_message;

public:
    GenericPlayer(const std::string& _name, IInteractive* message) : name(_name), m_message(message)
    {
        
    }

    virtual ~GenericPlayer()
    {
        
    }

    virtual bool isHitting() const = 0;

    bool isBoosted() const
    {
        if (GetTotal() > 21) 
        {
            return true;
        }
        return false;
    }

    void Bust() const
    {
        m_message->message(name);
        m_message->message("Is Over");
    }
};

class Player : public GenericPlayer
{
    public:
    Player(const std::string& _name, IInteractive* message) : GenericPlayer(_name, message)
    {

    }
    bool isHitting() const
    {
        //.............
    }

};

template <class T>
class Pair1
{
private:
    T m_first;
    T m_second;

public:
    Pair1(T first, T second) : 
        m_first(first), m_second(second)
    {

    }

    T first() const
    {
        return m_first;
    }

    T second() const
    {
        return m_second;
    }
};

template <class T, class T1>
class Pair
{
private:
    T m_first;
    T1 m_second;

public:
    Pair(T first, T1 second) : 
        m_first(first), m_second(second)
    {

    }

    T first() const
    {
        return m_first;
    }

    T1 second() const
    {
        return m_second;
    }
};

template <class U>
class Pair<std::string, U>
{
private:
    std::string m_first;
    U m_second;

public:
    virtual ~Pair()
    {

    }

    Pair(std::string first, U second) : 
        m_first(first), m_second(second)
    {

    }

    std::string first() const
    {
        return m_first;
    }

    U second() const
    {
        return m_second;
    }
};



template <class T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(std::string first, T second) : Pair<std::string, T>::Pair(first, second)
    {

    }

};

int main(int argc, char const *argv[])
{
    std::cout << "First Task" << std::endl << std::endl;
    Pair1<int> p1(6, 9);
    std::cout << "Pair: " << p1.first() << " " << p1.second() << std::endl;

    Pair1<double> p2(3.4, 7.8);
    std::cout << "Pair: " << p2.first() << " " << p2.second() << std::endl;
    std::cout << "=============================================" << std::endl;

    std::cout << "Second Task" << std::endl << std::endl;
    Pair<int, double> p3(6, 7.8);
    std::cout << "Pair: " << p3.first() << " " << p3.second() << std::endl;

    Pair<double, int> p4(3.4, 5);
    std::cout << "Pair: " << p4.first() << " " << p4.second() << std::endl;
    std::cout << "=============================================" << std::endl;
    
    std::cout << "Third Task" << std::endl << std::endl;
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << " " << svp.second() << std::endl;
    std::cout << "=============================================" << std::endl;

    IInteractive* i = new Interactive;
    Player p("Andrew", i);
    p.Bust();
    delete i;
    return 0;
}
