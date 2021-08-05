#include "iostream"
#include "cmath"
#include "cstdint"

#define COUNT 10


//Первое задание
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

//Второе задание
class RGBA {

private:
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;

public:
    RGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255)
        :m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {

        }

    void print() {
        std::cout << "R" << static_cast<int>(m_red) << " G" << static_cast<int>(m_green) 
            << " B" << static_cast<int>(m_blue) << " ALPHA" << static_cast<int>(m_alpha) << std::endl;
    }

};

//Третье задание
class Stack {
private:
    int* m_stack;
    int m_lenght;

public:
    Stack() {
        m_stack = new int[COUNT];
        m_lenght = 0;
    }
    ~Stack() {
        delete [] m_stack;
    }

    void reset() {
        for(int i = 0; i < COUNT; i++)
            m_stack[i] = 0;

        m_lenght = 0;
    }

    void print() {
        if(!m_lenght) {
             std::cout << "( )" << std::endl;
             return;
        }
        std::cout << "( ";
        for(int i = 0; i < m_lenght; i++) {
            std::cout << m_stack[i] << " ";
        }
        std::cout << ")" << std::endl;
    }

    bool push(int value) {
        if(m_lenght == COUNT)
            return false;

        m_stack[m_lenght] = value;
        m_lenght++;

        return true;
    }

    bool isEmpty() {
        if(!m_lenght) return true;
        return false;
    }

    int pop() {
            return m_stack[--m_lenght];
    }
};

int main() {
    
    Power firsttask;
    firsttask.setFields(5,2);
    firsttask.printFilelds();
    std::cout << firsttask.calculate() << std::endl;

    RGBA secondtask(5,15,2,125);
    secondtask.print();

    Stack thirdtask;
    thirdtask.print();

    if(!thirdtask.isEmpty()) std::cout << thirdtask.pop() << std::endl;
    else std::cout << "Stack is empty!" << std::endl;

    thirdtask.print();
    if(!thirdtask.push(5)) std::cout << "Stack is full!" << std::endl;
    thirdtask.print();
    

    if(!thirdtask.isEmpty()) std::cout << thirdtask.pop() << std::endl;
    else std::cout << "Stack is empty!" << std::endl;

    if(!thirdtask.push(6)) std::cout << "Stack is full!" << std::endl;
    if(!thirdtask.push(7)) std::cout << "Stack is full!" << std::endl;
    if(!thirdtask.push(8)) std::cout << "Stack is full!" << std::endl;
    thirdtask.print();
    
    if(!thirdtask.isEmpty()) std::cout << thirdtask.pop() << std::endl;
    else std::cout << "Stack is empty!" << std::endl;
    
    thirdtask.print();
    thirdtask.reset();
    thirdtask.print();
    return 0;
}