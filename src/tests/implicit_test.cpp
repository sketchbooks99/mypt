#include <iostream>

#define IS_EXPLICIT 0

struct Data {
    int a;
    float b;
    std::string name;
};

class DataContainer {
public:
    DataContainer(int a, float b, const std::string& name)
    : m_a(a), m_b(b), m_name(name) {}

#if IS_EXPLICIT
    // ng
    explicit operator Data() { 
        Data data;
        data.a = m_a; 
        data.b = m_b;
        data.name = m_name;
        return data;
    }
#else
    // ok
    operator Data() {
        Data data;
        data.a = m_a; 
        data.b = m_b;
        data.name = m_name;
        return data;
    }
#endif

private:
    int m_a;
    float m_b;
    std::string m_name;
};

void func(const Data& data)
{
    std::cout << "a: " << data.a;
    std::cout << ", b: " << data.b;
    std::cout << ", name: " << data.name;
    std::cout << std::endl;
}

int main() {
    DataContainer container(1,2.0f, "container");
    func(container);
    return 0;
}