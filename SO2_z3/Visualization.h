#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "Client.h"
#include "Distributor.h"
#include "SalesMan.h"
#include <vector>
class Visualization {    
public:
    Visualization();
    void Start(Client clients[],Distributor distributors[],SalesMan salesmans[], vector<int> & gasolineQueue);
    virtual ~Visualization();
private:
    void CreateColors();
    void DrawFrame(int xcord, int ycord, int x, int y,int id);
    void DrawDistributors(int xcord, int ycord, int id);
    void MoveFrame(int xcord, int ycord, int x, int y, int id);
    void ClearFrame(int xcord, int ycord, int x, int y, int id);
    void ActualiseQueue();
    void SetDistributorStatus(int xcord, int ycord, bool status, int id);
    void SetQueue(int xcord, int ycord,int id);
    void Legend();
};

#endif /* VISUALIZATION_H */

