#include <cstdlib>
#include<iostream>
#include <thread>
#include "Visualization.h"
#include "Client.h"
#include "Car.h"
#include "Distributor.h"
#include "CarWash.h"
#include "SalesMan.h"
#include <vector>
#include <mutex>
#include <algorithm>
#include <unistd.h>
using namespace std;
mutex mx2;

vector <int> gasolineQueue;
vector <int> paymentQueue;
vector <int> washQueue;

static const int numOfClients=15;
static const int numOfDistributors=8;
static const int numOfSalesMans=4;

int xcords[8]={9,9,11,11,9,9,11,11};
int ycords[8]={42,44,42,44,62,64,62,64};

int sxcords = 14;
int sycords[4] = {86,89,93,96};

thread t[numOfClients];
Client clients[numOfClients];
Car cars[numOfClients];
Distributor distributors[numOfDistributors];
SalesMan salesmans[numOfSalesMans];
CarWash carwash = CarWash();
bool running = true;

void erase(vector<int>& v, int num){//function delete item of given value from vector
  size_t j = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] != num) v[j++] = v[i];
  }
  // trim vector to new size
  v.resize(j);
}
int RandomValue(){
    srand(time(NULL));
    return rand()%100+0;
}
void Run(Client *client){
    while(running){
        for(int i=0;i<numOfDistributors;i++){
            mx2.lock();
            if(client->waitToTank && !client->waitToPay && !distributors[i].isUsed && (gasolineQueue[0]==client->id || gasolineQueue.empty())){
                erase(gasolineQueue,client->id);
                    client->SetWaitToTank(false);
                    client->SetDistributorID(i);
                    distributors[client->distributorID].SetBussy(client->id);
                mx2.unlock();
                    client->Refuel(client);//go refuel
                    mx2.lock();
                    paymentQueue.push_back(client->id);//queue to pay for gasoline
                    mx2.unlock();
                    client->SetWaitToPay(true);
            }
            mx2.unlock();
        
        for(int j=0;j<numOfSalesMans;j++){
            mx2.lock();
                if((!client->waitToTank || !client->waitToWash)&& client->waitToPay && !salesmans[j].isWorking && (paymentQueue[0]==client->id || paymentQueue.empty())){
            mx2.unlock();
                mx2.lock();
                salesmans[j].SetBussy(client->id);
                client->SetSalesmanID(j);
                erase(paymentQueue,client->id);
                client->SetWaitToPay(false);
                mx2.unlock();
                client->Pay(client);//go pay
             
                mx2.lock();
                salesmans[client->salesmanID].SetFree();
                if(!client->waitToTank && !client->waitToWash)
                    distributors[client->distributorID].SetFree(); 
                if(carwash.isUsed && client->id==carwash.clientID && !client->waitToTank)
                    carwash.isUsed=false;
                mx2.unlock();
                client->Ride(client);//go for a ride
                
                if(RandomValue()<30){//go to refuel
                    client->SetWaitToTank(true);
                    mx2.lock();                
                    gasolineQueue.push_back(client->id);
                    mx2.unlock();
                }
                else{//go to carwash
                    mx2.lock();
                    vector<int>::iterator it=find(washQueue.begin(),washQueue.end(),client->id);
                    if(washQueue.end()==it){
                    client->waitToWash=true;
                    washQueue.push_back(client->id);
                    mx2.unlock();
                    }
                }            
            }
            mx2.unlock();
        }
        //car wash maintance
            mx2.lock();
            if(!carwash.isUsed && client->waitToWash && ((washQueue[0]==client->id || washQueue.empty()))){
                erase(washQueue,client->id);
                carwash.isUsed=true;
                carwash.clientID=client->id;
                mx2.unlock();
                client->Wash(client);
                mx2.lock();
                client->waitToWash=false;
                client->SetWaitToPay(true);
                mx2.unlock();
            }
            mx2.unlock();
        }
    }        
}
void CreateClientsAndCars(){//function create cars and clients
    for(int i=0;i<numOfClients;i++){
        clients[i] =  Client(i,false,true,false);//create new client passing id, waitopay and waittotank and wait to wash
        gasolineQueue.push_back(i); //add client to gasoline queue
        cars[i]=Car(i);//create cars passing id 
    }    
}
void CreateDistributors(){//function creates distributors
    for(int i=0;i<numOfDistributors;i++){
        distributors[i] =  Distributor(i,false,xcords[i],ycords[i]);//create new distributor passing id and it is used
    }
}
void CreateSalesMans(){//function creates distributors
    for(int i=0;i<numOfSalesMans;i++){
        salesmans[i] =  SalesMan(i,false,sxcords,sycords[i]);//create new salesman passing id and it is used
    }
}
int main(int argc, char** argv) {
    CreateClientsAndCars();
    CreateDistributors();
    CreateSalesMans();
    
    for(int i=0;i<numOfClients;i++){
        t[i]=thread(Run,&clients[i]); 
        usleep(100);
    }
    
    Visualization vs = Visualization();
    vs.Start(clients,distributors,salesmans,gasolineQueue,paymentQueue, washQueue, carwash);
    
    running=false;//stop philosophers function
    
    for(int i=0;i<numOfClients;i++){//join threads
        t[i].join();
    }
    return 0;
}
