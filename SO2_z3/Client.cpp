#include "Client.h"
#include <thread>
#include <random>
#include <chrono>
default_random_engine re;

Client::Client() {
}

Client::Client(int id,bool waitToPay, bool waitToTank) {
    this->id=id;
    this->waitToPay=waitToPay;
    this->waitToTank=waitToTank;
}
void Client :: Refuel(Client *c){    
    double time=GenerateRandomTime(2,5);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
void Client :: Pay(Client *c){    
    double time=GenerateRandomTime(2,5);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
void Client :: Ride(Client *c){    
    double time=GenerateRandomTime(2,9);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
double Client :: GenerateRandomTime(int a, int b){//function generates random time in seconds as double value
    uniform_real_distribution<double> unif(a,b);    
    double value=unif(re);
    return value;
}
Client::~Client() {
}

