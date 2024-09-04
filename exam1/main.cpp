#include <string>
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base Constructor\n"; }
    virtual ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived Constructor\n"; }
    ~Derived() override { std::cout << "Derived Destructor\n"; }
};

int main() {
    Derived d;
    return 0;
}

