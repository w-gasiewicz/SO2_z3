#include "SalesMan.h"

SalesMan::SalesMan() {
}

SalesMan::SalesMan(int id, bool isWorking,int xcord,int ycord) {
    this->id=id;
    this->isWorking=isWorking;
    this->xcord=xcord;
    this->ycord=ycord;
}

SalesMan::~SalesMan() {
}

