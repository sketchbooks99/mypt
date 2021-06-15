#include <string>
#include <iostream>

using namespace std;

string str(const string& s)
{
    return "str_" + s;
}

int main() {
    string s("hoge");
    cout << str(s).c_str() << endl;

    const char* s2 = "hoge";
    cout << s2 << endl;
}