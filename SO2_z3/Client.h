#ifndef CLIENT_H
#define CLIENT_H

class Client {
public:
    Client();
    Client(int id,bool waitToPay, bool waitToTank);
    virtual ~Client();
    
    int id;
    bool waitToTank;
    bool waitToPay;
private:

};

#endif /* CLIENT_H */
