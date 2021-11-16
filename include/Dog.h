#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "Toy.h"

using namespace std;

class Dog
{
  private:
    string name;
    SharedPtrToy favouriteToy;

  public:
    ~Dog() = default;
    Dog(string _name, SharedPtrToy* _toy): name(std::move(_name)), favouriteToy(SharedPtrToy(_toy)) {}

    void print()
    {
        cout << "-+-+-+-+-+-+-+-" << endl
             << "name: " << name << endl
             << "toy" << favouriteToy.getToy()->getName() << endl
             << "-+-+-+-+-+-+-+-" << endl;
    }

    void reset()
    {
        favouriteToy.itDelete();
        delete this;
    }
    void loseToy()
    {
        favouriteToy.itDelete();
    }
};