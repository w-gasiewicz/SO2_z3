#include "CarWash.h"
#include <mutex>
using namespace std;
mutex mxWash;

CarWash::CarWash() {
    isUsed=false;
}
void CarWash::SetBussy(int cID) {
    mxWash.lock();
    this->isUsed=true;
    this->clientID=cID;
    mxWash.unlock();
}
void CarWash::SetFree(){
    mxWash.lock();
    this->isUsed=false;
    mxWash.unlock();
}
CarWash::~CarWash() {
}

