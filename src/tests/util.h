#include <iostream>

template <typename T>
void Message_once(T val) {
    std::cout << val;
}

void Message() {
    std::cout << std::endl;
}

template <typename Head, typename... Args>
void Message(Head head, Args... args) {
    Message_once(head);
    if constexpr (sizeof...(args) > 0) std::cout << ' ';
    Message(args...);
}