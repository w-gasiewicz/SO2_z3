#ifndef CARWASH_H
#define CARWASH_H
#include <mutex>

using namespace std;
class CarWash {
public:
    CarWash();
    CarWash(const CarWash& orig);
    void SetFree();
    void SetBussy(int cID);
    int clientID;
    bool isUsed;
    virtual ~CarWash();
private:

};

#endif /* CARWASH_H */

