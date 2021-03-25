#include <iostream>
#include <vector>

template <typename T>
class VectorWrapper {
public:
    explicit VectorWrapper(size_t size) 
    { 
        m_values.resize(size);
    }
    explicit VectorWrapper(size_t size, const T& val) 
    { 
        m_values = std::vector<T>(size, val);
    } 

    T operator[] (int idx) const { return m_values[idx]; }
    T& operator[] (int idx) { return m_values[idx]; }

    void stream_values() {
        for (auto &v : m_values) {
            std::cout << v;
        }
        std::cout << std::endl;
    }
    void add_value(T val) { m_values.push_back(val); }
    std::vector<T> values() const { return m_values; }
    std::vector<T>& values() { return m_values; }

    size_t size() const { return m_values.size(); }
private:
    std::vector<T> m_values;
};

class Hoge {
public:
    Hoge(int a, int b) : a(a), b(b) {}
    friend std::ostream& operator<<(std::ostream& out, const Hoge& hoge);
private:
    int a, b;
};

std::ostream& operator<<(std::ostream& out, const Hoge& hoge) {
    return out << hoge.a << ' ' << hoge.b;
}

class Fuga {
public:
    Fuga(int a, int b, int c) : a(a), b(b), c(c) {}

    operator Hoge() { return Hoge(a, b); }
private:
    int a, b, c;
};

int main() {
    std::vector<int> v1 { 1,2,3,4 };
    std::vector<int> v2 { 5,6,7,8 };

    std::copy(v2.begin(), v2.end(), std::back_inserter(v1));
    for (auto &v : v1) std::cout << v << ' ';
    std::cout << std::endl;

    int base = 0;
    std::vector<Hoge> hoge_vec;
    for (int i=0; i<5; i++) {
        hoge_vec.emplace_back(base+i*2, base+i*2+1);
    }
    base += 5*2;
    std::vector<Fuga> fuga_vec;
    for (int i=0; i<5; i++) {
        fuga_vec.emplace_back(base+i*3, base+i*3+1, base+i*3+2);
    }

    std::copy(fuga_vec.begin(), fuga_vec.end(), std::back_inserter(hoge_vec));

    for (auto& h : hoge_vec) std::cout << h << std::endl;

    std::vector<Hoge> hoges;
    for (int i=0; i<10; i++) {
        Fuga fuga(i*3, i*3+1, i*3+2);
        hoges.emplace_back(fuga);
    }
    for (auto& h : hoges) std::cout << h << ' ';
    std::cout << std::endl;

    // Vector wrapper
    VectorWrapper<float> f_vw(10);
    for (size_t i=0; i<f_vw.size(); i++) {
        f_vw[i] = (float)i;
    }
    f_vw.stream_values();

    for (auto& v : f_vw.values()) {
        v *= 2.f;
    }
    f_vw.stream_values();

    return 0;
}