#include <iostream>

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;

public:
    Date(int day, int month, int year) : 
        m_day(day), m_month(month), m_year(year)
    {

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

int main(int argc, char const *argv[])
{
    Date date(29, 8, 2021);
    std::cout << date << std::endl;
    return 0;
}
