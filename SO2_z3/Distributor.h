#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H
#include <mutex>
class Distributor {
public:
    Distributor();
    Distributor(int id, bool isUsed,int xcord, int ycord,int clientID);
    void SetFree();
    void SetBussy();
    virtual ~Distributor();    
    int id,xcord,ycord,clientID;
    bool isUsed;
private:
};

#endif /* DISTRIBUTOR_H */

