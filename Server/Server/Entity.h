#pragma once
#include<string>
using namespace std;
template<typename ID>
class Entity {

private:
    ID id=0;
public:
    ID getId();
    void setId(ID id);
    virtual string toString()=0;
};


template<typename ID>
void Entity<ID>::setId(ID id) {
    this->id = id;
}

template<typename ID>
ID Entity<ID>::getId() {
    return this->id;
}