#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H
#include <mutex>
class Distributor {
public:
    Distributor();
    Distributor(int id, bool isUsed,int xcord, int ycord);
    void SetFree();
    void SetBussy(int cID);
    virtual ~Distributor();    
    int id,xcord,ycord,clientID;
    bool isUsed;
private:
};

#endif /* DISTRIBUTOR_H */

