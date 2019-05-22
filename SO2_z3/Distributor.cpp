#include "Distributor.h"
#include <mutex>
using namespace std;
mutex mx;

Distributor::Distributor() {
}

Distributor::Distributor(int id, bool isUsed,int xcord,int ycord,int clientID) {
    this->id=id;
    this->isUsed=isUsed;
    this->xcord=xcord;
    this->ycord=ycord;
    this->clientID=clientID;
}
void Distributor::SetBussy(int cID) {
    mx.lock();
    this->isUsed=true;
    //this->clientID=cID;
    mx.unlock();
}
void Distributor::SetFree(){
    mx.lock();
    this->isUsed=false;
    //this->clientID=99;
    mx.unlock();
}

Distributor::~Distributor() {
}

