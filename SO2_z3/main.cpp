#include <cstdlib>
#include <thread>
#include "Visualization.h"
#include "Client.h"
#include "Car.h"
#include "Distributor.h"
#include "SalesMan.h"
#include <mutex>
using namespace std;
mutex mx2;
static const int numOfClients=7;
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

void Run(Client *client){
    while(running){
        for(int i=0;i<numOfDistributors;i++){
            if(!distributors[i].isUsed){
                //mx2.lock();
                distributors[i].SetBussy();
                distributors[i].clientID=client->id;
                client->Refuel(client);
                distributors[i].SetFree();
                //mx2.unlock();
            }
        }
    }        
}
void CreateClientsAndCars(){//function create cars and clients
    for(int i=0;i<numOfClients;i++){
        clients[i] =  Client(i,false,false);//create new client passing id, waitopay and waittotank
        cars[i]=Car(i);//create cars passing id 
    }    
}
void CreateDistributors(){//function creates distributors
    for(int i=0;i<numOfDistributors;i++){
        distributors[i] =  Distributor(i,false,xcords[i],ycords[i],0);//create new distributor passing id and it is used
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
    }
    
    Visualization vs = Visualization();
    vs.Start(clients,distributors,salesmans);
    
    running=false;//stop philosophers function
    
    for(int i=0;i<numOfClients;i++){//join threads
        t[i].join();
    }
    return 0;
}
