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
    Client(int id,bool waitToPay, bool waitToTank);
    virtual ~Client();
    void Refuel(Client *c);
    int id;
    bool waitToTank;//client is waiting to tank vehicle
    bool waitToPay;//client is waiting to pay
private:    
    double GenerateRandomTime();
    chrono::high_resolution_clock::time_point start , stop;

};

#endif /* CLIENT_H */
