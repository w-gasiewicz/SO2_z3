#include <mutex>
#include "SalesMan.h"

using namespace std;
mutex mxSalesMan;
SalesMan::SalesMan() {
}

SalesMan::SalesMan(int id, bool isWorking,int xcord,int ycord,int clientID) {
    this->id=id;
    this->isWorking=isWorking;
    this->xcord=xcord;
    this->ycord=ycord;
    this->clientID=clientID;
}
void SalesMan::SetBussy(int cID){
 mxSalesMan.lock();
 this->isWorking=true;
 //this->clientID=cID;
 mxSalesMan.unlock();
}
void SalesMan::SetFree(){
mxSalesMan.lock();
this->isWorking=false;
mxSalesMan.unlock();
}
SalesMan::~SalesMan() {
}

