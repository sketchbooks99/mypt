#include <iostream>
#include <vector>

class Base {
public:
    virtual void print_members() const = 0;
};

class DerivedA : public Base {
public:
    DerivedA(int a, float b) : m_a(a), m_b(b) {}

    void print_members() const override {
        std::cout << m_a << ' ' << m_b << std::endl;
    }

private:
    int m_a;
    float m_b;
};

class DerivedB : public Base {
public:
    DerivedB(int a, float b, double c) : m_a(a), m_b(b), m_c(c) {}

    void print_members() const override {
        std::cout << m_a << ' ' << m_b << ' ' << m_c << std::endl;
    }
private:
    int m_a;
    float m_b;
    double m_c;
};

void construct_derivedA(Base** ptr, int a, float b) {
    *ptr = new DerivedA(a, b);
}

void construct_derivedB(Base** ptr, int a, float b, double c) {
    *ptr = new DerivedB(a, b, c);
}

int main() {
    std::vector<Base**> bases;
    for (int i=0; i<10; i++) {
        bases.push_back((Base**)malloc(sizeof(Base**)));
        if (i%2 == 0) 
            construct_derivedA(bases.back(), i, (float)i*1.5f);
        else
            construct_derivedB(bases.back(), i, (float)i*1.5f, (double)i*2.25);
    }

    for (auto& b : bases) (*b)->print_members();
}