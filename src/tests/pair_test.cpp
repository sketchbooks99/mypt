#include "../core/vec.h"
#include <utility>
#include <vector>

using namespace mypt;
using namespace std;

class Base {
public:
    virtual string name() const = 0;
};

class DerivedA final : public Base {
public:
    string name() const override { return "DerivedA"; }
};

class DerivedB final : public Base {
public:
    string name() const override { return "DerivedB"; }
};

int main() {
    pair<vector<DerivedA>, vector<Base*>> pairs;
    for (int i=0; i<5; i++) {
        pairs.first.push_back(DerivedA());
        if ( i%2 == 0 )
            pairs.second.push_back(new DerivedA());
        else 
            pairs.second.push_back(new DerivedB());
    }
    
    for ( auto& first : pairs.first ) std::cout << first.name();
    for ( auto& second : pairs.second ) std::cout << second->name();

    return 0;
}