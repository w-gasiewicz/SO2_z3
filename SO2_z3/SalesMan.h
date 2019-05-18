#ifndef SALESMAN_H
#define SALESMAN_H

class SalesMan {
public:
    SalesMan();
    SalesMan(int id, bool isUsed,int xcord,int ycord,int clientID);
    int id,xcord,ycord,clientID;
    bool isWorking;
    virtual ~SalesMan();
private:

};

#endif /* SALESMAN_H */

