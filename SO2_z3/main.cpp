#include <cstdlib>
#include<iostream>
#include <thread>
#include "Visualization.h"
#include "Client.h"
#include "Car.h"
#include "Distributor.h"
#include "SalesMan.h"
#include <vector>
#include <mutex>
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

bool running = true;

void erase(vector<int>& v, int num){//function delete item of given value from vector
  size_t j = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] != num) v[j++] = v[i];
  }
  // trim vector to new size
  v.resize(j);
}
void Run(Client *client){
    while(running){
        //for(int k=0;k<gasolineQueue.size();k++)
       // if(client->id==gasolineQueue[0]){
        for(int i=0;i<numOfDistributors;i++){
            if(!distributors[i].isUsed && client->waitToTank && gasolineQueue[0]==client->id){
                    //client->waitToTank=false;
                    client->SetWaitToTank(false);
                    erase(gasolineQueue,client->id);
                    distributors[i].SetBussy(client->id);
                    distributors[i].clientID=client->id;
                    client->Refuel(client);//go refuel
                    paymentQueue.push_back(client->id);//queue to pay for gasoline
                    //client->waitToPay=true;
                    client->SetWaitToPay(true);
            }
        /*    for(int j=0;j<numOfSalesMans;j++){
            if(!salesmans[j].isWorking && client->waitToPay){
                salesmans[j].SetBussy(client->id);
                salesmans[j].clientID=client->id;
                erase(paymentQueue,client->id);
                //client->waitToPay=false;
                client->SetWaitToPay(false);
                client->Pay(client);//go pay
                salesmans[j].SetFree();
            }
        }*/
        if(!client->waitToPay && !client->waitToTank){
            distributors[i].SetFree();
            client->Ride(client);//go for a ride
            //client->waitToTank=true;//stay in queue for tank
            client->SetWaitToTank(true);
            gasolineQueue.push_back(client->id);
            }
        }        
        for(int j=0;j<numOfSalesMans;j++){
            if(!salesmans[j].isWorking && client->waitToPay){
                salesmans[j].SetBussy(client->id);
                salesmans[j].clientID=client->id;
                erase(paymentQueue,client->id);
                client->SetWaitToPay(false);
                client->Pay(client);//go pay
                salesmans[j].SetFree();
            }
        }
        //}
        //car wash maintance
    }        
}
void CreateClientsAndCars(){//function create cars and clients
    for(int i=0;i<numOfClients;i++){
        clients[i] =  Client(i,false,true);//create new client passing id, waitopay and waittotank
        gasolineQueue.push_back(i); //add client to gasoline queue
        cars[i]=Car(i);//create cars passing id 
    }    
}
void CreateDistributors(){//function creates distributors
    for(int i=0;i<numOfDistributors;i++){
        distributors[i] =  Distributor(i,false,xcords[i],ycords[i],99);//create new distributor passing id and it is used
    }
}
void CreateSalesMans(){//function creates distributors
    for(int i=0;i<numOfSalesMans;i++){
        salesmans[i] =  SalesMan(i,false,sxcords,sycords[i],99);//create new salesman passing id and it is used
    }
}
int main(int argc, char** argv) {
    CreateClientsAndCars();
    CreateDistributors();
    CreateSalesMans();
    
   /* for(int i=0;i<gasolineQueue.size();i++){
        cout<<gasolineQueue[i]<<endl;
    }
    erase(gasolineQueue,14);
    for(int i=0;i<gasolineQueue.size();i++){
        cout<<gasolineQueue[i]<<endl;
    }*/
    
    for(int i=0;i<numOfClients;i++){
        t[i]=thread(Run,&clients[i]); 
        usleep(100);
    }
    
    Visualization vs = Visualization();
    vs.Start(clients,distributors,salesmans,gasolineQueue,paymentQueue);
    
    running=false;//stop philosophers function
    
    for(int i=0;i<numOfClients;i++){//join threads
        t[i].join();
    }
    return 0;
}
