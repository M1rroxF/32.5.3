#include <iostream>
#include "Toy.h"
#include "Dog.h"

using namespace std;
int main(){
    SharedPtrToy ball("ball");
    SharedPtrToy bone("bone");

    Dog mrFirz("Firz", &ball);
    Dog mrKruz("Kruz", &bone);

    bone.reset();
    ball.reset();

    mrKruz.print();
    mrKruz.loseToy();
}