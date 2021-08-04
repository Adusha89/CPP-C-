#include "iostream"
#include "cmath"

class Power {
private:
    double m_base;
    double m_degree;

public:
    Power () : m_base(0), m_degree(0) {

    }

    void setFields (double base, double degree) {
        m_base = base;
        m_degree = degree;
    }

    double calculate () {
        return pow(m_base, m_degree);
    }

    void printFilelds () {
        std::cout << m_base << " " << m_degree << std::endl;
    }
};

int main() {
    
    Power a;
    a.setFields(5,2);
    a.printFilelds();
    std::cout << a.calculate() << std::endl;

    return 0;
}