#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <thread>
using namespace std;

class Toy
{
  string name;
  public:
    explicit Toy(string _name): name(std::move(_name)) {}
    string getName() { return name; }
    ~Toy() {}
};

///////////////////////////////////////////////////

/*
 * this.getInt() -->> count
 * this.getToy() -->> toy
 * this.assign(SharedPtrToy) -->> this = new SharedPtrToy
 * this.itDelete() -->> remove minor pointer
 * this.reset() -->> remove main pointer
 */

class SharedPtrToy
{
  private:
    Toy* toy{};
    int* count;

  public:
    void countPlus() {*count += 1;}
    //gets
    Toy* getToy() { return toy; }
    int* getInt() { return count; }

    //starts
    explicit SharedPtrToy(const string& _name): count(new int (0))
    {
        toy = new Toy(_name);
    }
    explicit SharedPtrToy(SharedPtrToy* _shToy): count(_shToy->getInt()), toy(_shToy->getToy()) { _shToy->countPlus(); }
    ~SharedPtrToy() = default;

    //functions
    void itDelete()
    {
        *count -= 1;
        count = nullptr;
        toy = nullptr;
    }
    static void ToDelete(SharedPtrToy* _toy){
        while (*_toy->getInt() > 0);
        delete _toy->getInt();
        delete _toy->getToy();
        delete _toy;
    }void reset() {
        thread c(ToDelete, this);
        c.detach();
    }
};