#include <cstdlib>
#include <thread>
#include "Visualization.h"
#include "Client.h"
#include "Car.h"
#include "Distributor.h"

using namespace std;

static const int numOfClients=5;
thread t[numOfClients];
Client clients[numOfClients];
Car cars[numOfClients];
Distributor distributors[numOfClients];
bool running = true;

void Run(Client *client){
    while(running){
    
    }        
}
void CreateClientsAndCars(){//function create cars and clients
    for(int i=0;i<numOfClients;i++){
        clients[i] =  Client(i,false,false);//create new client passing id, waitopay and waittotank
        cars[i]=Car(i);//create cars passing id 
    }    
}
void CreateDistributors(){
    for(int i=0;i<numOfClients;i++){
        distributors[i] =  Distributor(i,false);//create new client passing id and it is used
    }
}
int main(int argc, char** argv) {
    CreateClientsAndCars();
    CreateDistributors();
    
    Visualization vs = Visualization();
    vs.Start();
    return 0;
}
