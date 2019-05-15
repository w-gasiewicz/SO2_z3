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
void Distributor::SetBussy() {
    mx.lock();
    this->isUsed=true;
    mx.unlock();
}
void Distributor::SetFree(){
    mx.lock();
    this->isUsed=false;
    mx.unlock();
}
Distributor::~Distributor() {
}

