#ifndef CLIENT_H
#define CLIENT_H
#include <stdbool.h>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
class Client {
public:
    Client();
    Client(int id,bool waitToPay, bool waitToTank, bool waitToWash);
    virtual ~Client();
    void Refuel(Client *c);
    void Pay(Client *c);
    void Ride(Client *c);
    void Wash(Client *c);
    void SetWaitToPay(bool value);
    void SetWaitToTank(bool value);
    void SetDistributorID(int value);
    void SetSalesmanID(int value);
    int id,distributorID,salesmanID;
    bool waitToTank;//client is waiting to tank vehicle
    bool waitToPay;//client is waiting to pay
    bool waitToWash;
private:    
    double GenerateRandomTime(int a, int b);
    chrono::high_resolution_clock::time_point start , stop;

};

#endif /* CLIENT_H */
