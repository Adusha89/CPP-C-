#include <iostream>
#include <limits>
#include <vector>

void firtsTask()
{
    int n;

    std::cout << "Input n" << std::endl;

    while (!(std::cin >> n) || std::cin.peek() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error input, try yet!" << std::endl;
    }

    std::cout << n << std::endl;
}

std::ostream& endll(std::ostream& out)
{
    return (out << "\n\n" << std::flush);
}


class IInteractive
{
public:
    virtual ~IInteractive()
    {

    }
    virtual void message(std::string) const = 0;
    virtual bool question(std::string) = 0;
};

class Interactive : public IInteractive
{
public:

    virtual ~Interactive()
    {

    }

    void message(std::string message) const override
    {
        std::cout << message << std::endl;
    }

    virtual bool question(std::string message) override
    {
        char answer;
        std::cout << message << std::endl;
        std::cin >> answer;
        return (answer == 'y' || answer =='Y');
    }
};

class Card
{
public:

    enum Suit //Масть
    {
        clubs,
        diamonds, //пики
        hearts, //червы
        spades //трефы
    };

    enum Nominal
    {
        ace = 1,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        
    };

    bool m_isFaceUp = false; //рубашкой вверх

    Card(Suit suit, Nominal nominal, bool is_FaceUp = false)
        : m_suit(suit), m_nominal(nominal), m_isFaceUp(is_FaceUp)
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
            if (m_nominal > 10)
            {
                return m_nominal - m_nominal%10;
            }
            if ( m_nominal == 1)
            {
                return 11;
            }

            return m_nominal;
        }
        return 0;
        
    }

friend std::ostream& operator<<(std::ostream& , const Card& );
private:
    Suit m_suit;
    Nominal m_nominal;

};

std::ostream& operator<<(std::ostream& out, const Card& aCard)
{
    const std::string NOMINAL[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const std::string SUITS[] = {"C", "D", "H", "S"};
    if (aCard.m_isFaceUp)
    {
      return out << NOMINAL[aCard.m_nominal] << SUITS[aCard.m_suit];
    }
    else
    {
       return out << "XX";
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
                ++sum;
            }
            else
            {
                sum += card;
            }
        }
        return sum;
    }

    std::vector<Card*>& getm_Cards()
    {
        return m_Cards;
    }


};

class GenericPlayer : public Hand
{
private:
    std::string name;
    IInteractive* m_I;

public:
    GenericPlayer(std::string _name, IInteractive* _I) : name(_name), m_I(_I)
    {
        
    }

    virtual ~GenericPlayer()
    {
        
    }

    virtual bool isHitting() const = 0;

    bool isBoosted() const
    {
        return (GetTotal() > 21); 
    }

    void Bust() const
    {
        m_I->message(name);
        m_I->message("Is Over");
    }

    std::string getName() const
    {
        return name;
    }

    IInteractive* getI() const
    {
        return m_I;
    }

    friend std::ostream& operator<<(std::ostream&, const GenericPlayer&);
};

std::ostream& operator<<(std::ostream& os, GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.getName() << ":\t";
    
    std::vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.getm_Cards().empty())
    {
        for (pCard = aGenericPlayer.getm_Cards().begin();
             pCard != aGenericPlayer.getm_Cards().end();
             ++pCard)
        {
            os << *(*pCard) << "\t";
        }
        
        
        if (aGenericPlayer.GetTotal() != 0)
        {
            std::cout << "(" << +aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    
    return os;
};


class Player : public GenericPlayer
{
    public:
    virtual ~Player()
    {

    }

    Player(std::string _name, IInteractive* _I) : GenericPlayer(_name, _I)
    {

    }

    bool isHitting() const override
    {
        getI()->message(getName());
        return getI()->question("Do you need a card?");
    }

    void Win() const
    {
        getI()->message(getName());
        getI()->message("You WIN!");
    }

    void Lose() const
    {
        getI()->message(getName());
        getI()->message("You LOSE!");
    }

    void Push() const
    {
        getI()->message(getName());
        getI()->message("You Pushes!");
    }

};

class House : public GenericPlayer
{
public:
    House(std::string _name, IInteractive* _I) : GenericPlayer(_name, _I)
    {

    }
    
    virtual ~House()
    {

    }

    bool isHitting() const override
    {
        return (GetTotal() <= 16);
    }

    void FlipFirstCard()
    {
        if (!(getm_Cards().empty()))
        {
            getm_Cards()[0]->Flip();
        }
        else
        {
            getI()->message("No card!");
        }
    }
};

int main(int argc, char const *argv[])
{
    firtsTask();
    std::cout << endll;

    IInteractive* i = new Interactive;
    Player p("Andrew", i);

    std::cout << std::boolalpha<< p.isHitting() << std::endl;

    p.Win();
    p.Lose();
    p.Push();

    House h("House", i);
    h.Add(new Card(Card::hearts, Card::seven, true));
    h.Add(new Card(Card::hearts, Card::seven, true));

    std::cout << +h.GetTotal() << std::endl;

    std::cout << +h.GetTotal() << std::endl;

    std::cout << *(h.getm_Cards()[0]) << std::endl;
    std::cout << h << std::endl;

    return 0;
}

