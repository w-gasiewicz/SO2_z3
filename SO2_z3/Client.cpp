#include "Client.h"
#include <thread>
#include <random>
#include <chrono>
#include <mutex>
#include <bits/stl_bvector.h>
using namespace std;
mutex mxClient;

Client::Client() {
}

Client::Client(int id,bool waitToPay, bool waitToTank, bool waitToWash) {
    this->id=id;
    this->waitToPay=waitToPay;
    this->waitToTank=waitToTank;
    this->waitToWash=waitToWash;
}
void Client :: Refuel(Client *c){    
    double time=GenerateRandomTime(4,9);
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
void Client :: Wash(Client *c){    
    double time=GenerateRandomTime(2,4);
    int timeToWait=round(time*1000.0);
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
}
double Client :: GenerateRandomTime(int a, int b){//function generates random time in seconds as double value
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine generator (seed);
   std::uniform_real_distribution<double> distribution (a,b);
   return distribution(generator);
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
void Client :: SetDistributorID(int value){
    mxClient.lock();
    this->distributorID=value;
    mxClient.unlock();
}
void Client :: SetSalesmanID(int value){
    mxClient.lock();
    this->salesmanID=value;
    mxClient.unlock();
}
Client::~Client() {
}

