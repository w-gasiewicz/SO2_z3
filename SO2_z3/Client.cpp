#include "Client.h"

Client::Client() {
}

Client::Client(int id,bool waitToPay, bool waitToTank) {
    this->id=id;
    this->waitToPay=waitToPay;
    this->waitToTank=waitToTank;
}

Client::~Client() {
}

