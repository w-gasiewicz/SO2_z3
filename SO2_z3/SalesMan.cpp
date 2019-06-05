#include "SalesMan.h"

using namespace std;
SalesMan::SalesMan() {
}

SalesMan::SalesMan(int id, bool isWorking,int xcord,int ycord) {
    this->id=id;
    this->isWorking=isWorking;
    this->xcord=xcord;
    this->ycord=ycord;
}
void SalesMan::SetBussy(int cID){
 this->isWorking=true;
 this->clientID=cID;
}
void SalesMan::SetFree(){
this->isWorking=false;
}
SalesMan::~SalesMan() {
}

