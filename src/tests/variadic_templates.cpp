#include <iostream>
#include <tuple>
#include <string>
#include <vector>

#define OK 1

// ----------------------------------------------------------------------
struct Base {
    virtual void print_member() const = 0;
};

struct Hoge : public Base {
    Hoge(char a, int b, const std::string& str)
    : a(a), b(b), str(str) {}
    char a;
    int b;
    std::string str;

    void print_member() const override {
        std::cout << (int)a << ' ' << b << ' ' << str << std::endl;
    }
};

struct Fuga : public Base {
    Fuga(char a, int b, float c, double d, const std::string& str)
    : a(a), b(b), c(c), d(d), str(str) {}
    char a;
    int b;
    float c;
    double d;
    std::string str;

    void print_member() const override {
        std::cout << (int)a << ' ' << b << ' ' << c << ' ' << d << ' ' << str << std::endl;
    }
};

// ----------------------------------------------------------------------
class FugaFuga {
public:
    // OK   
    template <typename ...Args>
    void create1(Args... args)
    {
        _create(args...);
    }


    template <typename ...Args>
    void create2(Args... args)
    {
        const size_t num_args = sizeof...(args);
        #if OK
        if constexpr (num_args == 1) _create_1(args...);
        if constexpr (num_args == 2) _create_2(args...);
        if constexpr (num_args == 3) _create_3(args...);
        if constexpr (num_args == 4) _create_4(args...);
        #else 
        if (num_args == 1) _create_1(args...);
        if (num_args == 2) _create_2(args...);
        if (num_args == 3) _create_3(args...);
        if (num_args == 4) _create_4(args...);
        #endif
    }

    void print_members() {
        std::cout << a << ' ' << b << ' ' << c << ' ' << d << std::endl;
    }
private:
    void _create(int a) { this->a = a; }
    void _create_1(int a) { this->a = a; }
    void _create(int a, float b) { this->a = a; this->b = b; }
    void _create_2(int a, float b) { this->a = a; this->b = b; }
    void _create(int a, float b, double c)
    {
        this->a = a; this->b = b; this->c = c;
    }
    void _create_3(int a, float b, double c)
    {
        this->a = a; this->b = b; this->c = c;
    }
    void _create(int a, float b, double c, const std::string& d)
    {
        this->a = a; this->b = b; this->c = c; this->d = d;
    }
    void _create_4(int a, float b, double c, const std::string& d)
    {
        this->a = a; this->b = b; this->c = c; this->d = d;
    }

    int a { 0 };
    float b { 0.f };
    double c { 0.0 };
    std::string d { "Default" };
};

// ----------------------------------------------------------------------
template <typename T, typename... Args>
void construct(T** ptr, Args... args) {
    (*ptr) = new T(args...);
}

void construct_hoge(Base** ptr, char a, int b, const std::string& str)
{
    (*ptr) = new Hoge(a, b, str);
}


std::ostream& operator<<(std::ostream& out, const Hoge& hoge) {
    return out << (int)hoge.a << ' ' << hoge.b << ' ' << hoge.str << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Fuga& fuga) {
    return out << (int)fuga.a << ' ' << fuga.b << ' ' << fuga.c << ' ' << fuga.d << ' ' << fuga.str << std::endl;
}

// ----------------------------------------------------------------------
template <typename T>
void free_object(T* obj) {
    delete obj;
}

void free_objects() {
    std::cout << "End of recursive free." << std::endl;
}

template <typename Head, typename... Args>
void free_objects(Head* head, Args... args)
{
    free_object(head);
    free_objects(args...);
}

// ----------------------------------------------------------------------
void print_something() { 
    std::cout << "The end of print_something()" << std::endl;
}

template <typename Head, typename... Args>
void print_something(Head head, Args... args) {
    std::cout << head << std::endl;
    print_something(args...);
}

template <typename T, typename... Args>
void call_variadic(T data, Args... args) {
    std::cout << data << std::endl;
    print_something(args...);
}

template <typename T, typename ...Args>
void call_variadic_wrapper(T data, Args... args) {
    call_variadic(data, args...);
}

int main() {
    Hoge* hoge = new Hoge(1,2,"hoge1");
    std::cout << *hoge << std::endl;
    construct(&hoge, 3, 4, "hoge2");
    std::cout << *hoge << std::endl;

    // Basic pointer
    std::vector<Base*> bases(10);
    for(size_t i=0; i<bases.size(); i++) {
        bases[i] = (Base*)malloc(sizeof(Base*));
        if (i%2 == 0)
            construct((Hoge**)&bases[i], (char)i*2, i*2+1, "hoge"+std::to_string(i));
        else 
            construct((Fuga**)&bases[i], (char)i*2, i*2+1, (float)(i*2+2), (double)(i*2+3), "fuga"+std::to_string(i));
    }
    for(auto& b : bases) b->print_member();

    std::vector<FugaFuga> fugas(4);
    fugas[0].create2(1);
    fugas[1].create2(1, 2.f);
    fugas[2].create2(1, 2.f, 3.0);
    fugas[3].create2(1, 2.f, 3.0, "Not default");
    for (auto& f : fugas) f.print_members();

    // pointer test
    std::cout << "Construct hoges..." << std::endl;
    Hoge* h1 = new Hoge(1,2,"hoge1");
    Hoge* h2 = new Hoge(3,4,"hoge2");
    Hoge* h3 = new Hoge(5,6,"hoge3");
    Hoge* h4 = new Hoge(7,8,"hoge4");
    Hoge* h5 = new Hoge(9,10,"hoge5");
    h1->print_member();
    h2->print_member();
    h3->print_member();
    h4->print_member();
    h5->print_member();

    std::cout << "Start free hoges..." << std::endl;
    free_objects(h1, h2, h3, h4, h5);

    // h5->print_member(); // NG ... Segmentation fault

    call_variadic_wrapper(1,2,3,4,5,6);
}

