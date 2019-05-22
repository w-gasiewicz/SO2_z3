#include "Client.h"
#include <thread>
#include <random>
#include <chrono>
#include <mutex>
#include <bits/stl_bvector.h>
default_random_engine re;
using namespace std;
mutex mxClient;

Client::Client() {
}

Client::Client(int id,bool waitToPay, bool waitToTank) {
    this->id=id;
    this->waitToPay=waitToPay;
    this->waitToTank=waitToTank;
}
void Client :: Refuel(Client *c){    
    double time=GenerateRandomTime(15,20);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
void Client :: Pay(Client *c){    
    double time=GenerateRandomTime(2,5);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
void Client :: Ride(Client *c){    
    double time=GenerateRandomTime(2,4);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
double Client :: GenerateRandomTime(int a, int b){//function generates random time in seconds as double value
    uniform_real_distribution<double> unif(a,b);    
    double value=unif(re);
    return value;
}
void Client :: SetWaitToPay(bool value){
    mxClient.lock();
    this->waitToPay=value;
    mxClient.unlock();
}
void Client :: SetWaitToTank(bool value){
    mxClient.lock();
    this->waitToTank=value;
    mxClient.unlock();
}
Client::~Client() {
}

