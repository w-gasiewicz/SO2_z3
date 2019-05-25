#ifndef SALESMAN_H
#define SALESMAN_H
#include <mutex>
class SalesMan {
public:
    SalesMan();
    SalesMan(int id, bool isUsed,int xcord,int ycord);
    void SetBussy(int cID);
    void SetFree();
    int id,xcord,ycord,clientID;
    bool isWorking;
    virtual ~SalesMan();
private:

};

#endif /* SALESMAN_H */

