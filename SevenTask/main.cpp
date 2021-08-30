#include <iostream>
#include <vector>
#include <algorithm>

class IInteractive
{
public:
    virtual ~IInteractive()
    {

    }
    virtual void message(const std::string&) const = 0;
    virtual bool question(std::string) = 0;
};

class Interactive : public IInteractive
{
public:

    virtual ~Interactive()
    {

    }
    
    void message(const std::string& message) const override
    {
        std::cout << message;
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

    bool m_isFaceUp;
    Card(Suit suit, Nominal nominal, bool is_FaceUp = true)
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
    IInteractive* m_I;

public:
    Hand(){}
    Hand(IInteractive* _I) : m_I(_I) {}
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

    IInteractive* getI() const
    {
        return m_I;
    }


};

class GenericPlayer : public Hand
{
private:
    std::string name;

public:
    GenericPlayer(){}
    GenericPlayer(std::string _name, IInteractive* _I) : name(_name), Hand(_I)
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
        getI()->message(name);
        getI()->message(" Is Over\n");
    }

    std::string getName() const
    {
        return name;
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
        return getI()->question(" Do you need a card?");
    }

    void Win() const
    {
        getI()->message(getName());
        getI()->message(" You WIN!\n");
    }

    void Lose() const
    {
        getI()->message(getName());
        getI()->message(" You LOSE!\n");
    }

    void Push() const
    {
        getI()->message(getName());
        getI()->message(" You Pushes!\n");
    }

};

class House : public GenericPlayer
{
public:
    House(){}
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

class Deck : public Hand
{
public:
    Deck()
    {
        getm_Cards().reserve(52);
        Populate();
    }

    virtual ~Deck() {}

    void Populate()
    {
        Clear();

        for (uint8_t s = Card::clubs; s <= Card::spades; ++s)
        {
            for (uint8_t n = Card::ace; n <= Card::king; ++n)
            {
                Add(new Card(static_cast<Card::Suit>(s), static_cast<Card::Nominal>(n)));
            }
        }
    }

    void Shuffle()
    {
        random_shuffle(getm_Cards().begin(), getm_Cards().end());
    }

    void Deal(Hand& aHand)
    {
    if (!getm_Cards().empty())
        {
            aHand.Add(getm_Cards().back());
            getm_Cards().pop_back();
        }
    else
        {
            getI()->message("Out of cards. Unable to deal.");
        }
    }

    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        std::cout << std::endl;
        
        while (!(aGenericPlayer.isBoosted()) && aGenericPlayer.isHitting())
        {
            Deal(aGenericPlayer);
            std::cout << aGenericPlayer << std::endl;
            
            if (aGenericPlayer.isBoosted())
            {
                aGenericPlayer.Bust();
            }
        }   
    }
};

class Game
{
private:
    IInteractive* m_I;
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
    

public:
    Game(const std::vector<std::string>& names, IInteractive* _I) : m_I(_I), m_House("House", _I)
    {
        std::vector<std::string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName, _I));
        }
        
        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();

    }

    void Play()
    {
        std::vector<Player>::iterator pPlayer;
        for (uint8_t i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }
        
        m_House.FlipFirstCard();
        
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            std::cout << *pPlayer << std::endl;
        }
        std::cout << m_House << std::endl;
        
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.AdditionalCards(*pPlayer);
        }
        
        m_House.FlipFirstCard();
        std::cout << std::endl << m_House;
        
        m_Deck.AdditionalCards(m_House);
        
        if (m_House.isBoosted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->isBoosted()))
                {
                    pPlayer->Win();
                }
            }
        }
        else
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
                ++pPlayer)
            {
                if (!(pPlayer->isBoosted()))
                {
                    if (pPlayer->GetTotal() > m_House.GetTotal())
                    {
                        pPlayer->Win();
                    }
                    else if (pPlayer->GetTotal() < m_House.GetTotal())
                    {
                        pPlayer->Lose();
                    }
                    else
                    {
                        pPlayer->Push();
                    }
                }
            }
            
        }
        
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            pPlayer->Clear();
        }
        m_House.Clear();
    }


};

template<class T>
class Smart_ptr
{
private:
    T* m_ptr;

public:

    Smart_ptr(const Smart_ptr& smptr) : m_ptr(smptr.m_ptr)
    {

    }

    Smart_ptr(Smart_ptr& smptr)
    {
        m_ptr = smptr.m_ptr;
        smptr.m_ptr = nullptr;
    }

    Smart_ptr(T* ptr = nullptr) : m_ptr(ptr)
    {
        std::cout << "New smptr\n";
    }

    ~Smart_ptr()
    {
        delete m_ptr;
        std::cout << "Delete smptr\n";
    }

    T& operator* () const
    {
        return *m_ptr;
    }

    T* operator-> () const
    {
        return m_ptr;
    }

    Smart_ptr& operator=(Smart_ptr& smptr)
    {
        if (&smptr == this)
        {
            return *this;
        }

        delete m_ptr;
        m_ptr = smptr.m_ptr;
        smptr.m_ptr = nullptr;

        return *this;
    }

    operator bool()
    {
        return !(m_ptr == nullptr);
    }
};

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;

public:

    Date(int day = 0, int month = 0, int year = 0) : 
        m_day(day), m_month(month), m_year(year)
    {

    }

    void setDay(const int& day)
    {
        m_day = day;
    }

    void setMonth(const int& month)
    {
        m_month = month;
    }

    void setYear(const int& year)
    {
        m_year = year;
    }

    void setDate(const int& day, const int& month, const int& year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }

    int getDay() const
    {
        return m_day;
    }

    int getMonth() const
    {
        return m_month;
    }

    int getYear() const
    {
        return m_year;
    }
};

std::ostream& operator<<(std::ostream& out, const Date& date)
{
    return out << date.getDay() << " " << date.getMonth() << " " << date.getYear();
}

const Smart_ptr<Date>& compareDate(const Smart_ptr<Date>& date1, const Smart_ptr<Date>& date2)
{
    if (date1->getYear() != date2->getYear())
    {
        return (date1->getYear() > date2->getYear()) ? date1 : date2;
    }
    else
    {
        if (date1->getMonth() != date2->getMonth())
        {
            return (date1->getMonth() > date2->getMonth()) ? date1 : date2;
        }
        else 
        {
            return (date1->getDay() > date2->getDay()) ? date1 : date2;
        }
    }
}

void swapDate (Smart_ptr<Date>& date1, Smart_ptr<Date>& date2)
{
    Smart_ptr<Date> swap;
    swap = date1;
    date1 = date2;
    date2 = swap;
}

int main(int argc, char const *argv[])
{
    std::cout << "First Task\n" << std::endl;
    Smart_ptr<Date> today(new Date(30,8,2021));
    Smart_ptr<Date> date;
    
    std::cout << *today << std::endl;

    today->setDate(31,8,2021);
    std::cout << today->getDay() << std::endl;
    std::cout << today->getMonth() << std::endl;
    std::cout << today->getYear() << std::endl;

    today->setDay(1);
    today->setMonth(9);
    today->setYear(2021);

    std::cout << *today << std::endl;

    date = today;

    std::cout << *date << std::endl;

    if (!today) 
    {
        std::cout << "Pointer TODAY is null" << std::endl << std::endl;
    }

    if (!date) 
    {
        std::cout << "Pointer DATE is null" << std::endl;
    }

    std::cout << std::endl << "Second Task\n" << std::endl;
    

    Smart_ptr<Date> date1(new Date(21,9,2021));
    Smart_ptr<Date> date2(new Date(21,10,2021));

    std::cout << *compareDate(date1, date2) << std::endl;

    swapDate(date1, date2);

    std::cout << *date1 << std::endl;
    std::cout << *date2 << std::endl;

    std::cout << std::endl << "Third Task\n" << std::endl;
    
    IInteractive* i = new Interactive;

    while (true)
    {
        size_t count_players;
        std::cout << "Input count Players :";

        while (!(std::cin >> count_players) || std::cin.peek() != '\n'
                    || count_players < 1 || count_players > 10)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error input, try yet!" << std::endl;
        }
        std::vector<std::string> names;
        std::string n;

        char yet;

        for (size_t idx = 0; idx < count_players; ++idx)
        {
            std::cout << "Input name player :";
            std::cin >> n;
            names.push_back(n);
        }

        Game game(names, i);
        game.Play();

        std::cout << "Continue a game? (Y/N) : ";
        std::cin >> yet;
        if(!(yet == 'y' || yet == 'Y'))
        {
            break;
        }

    }
    
    delete i;

    return 0;
}
