#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

class Distributor {
public:
    Distributor();
    Distributor(int id, bool isUsed);
    virtual ~Distributor();
    
    int id;
    bool isUsed;
private:

};

#endif /* DISTRIBUTOR_H */

