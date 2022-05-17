#ifndef SWITCH_H
#define SWITCH_H

#include <string>
#include <functional>
#include <iostream>
#include <vector>


class Switchable {

};


template <class T>
struct _Case{
    T value;
    std::function <void()> callback;
};

template <class T>
class Switch {
    T value;
    std::vector<_Case<T>> cases;


public:
    Switch(T v) : value{v} {}

    Switch & Case(T value, std::function <void()> c) {
        this->cases.push_back(_Case<T>{value, c});
        return *this;
    }

    bool exec() {
        for(auto c : cases) {
            if(value == c.value) {
                c.callback();
                return false;
            }
        }

        return true;
    }
};





#endif // SWITCH_H
