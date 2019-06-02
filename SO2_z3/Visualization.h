#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "Client.h"
#include "Distributor.h"
#include "SalesMan.h"
#include "CarWash.h"
#include "GasStation.h"
#include <vector>
class Visualization {    
public:
    Visualization();
    void Start(Client clients[],Distributor distributors[],SalesMan salesmans[], vector<int> & gasolineQueue,vector<int> & paymentQueue, vector<int> & washQueue, CarWash & carwash, GasStation & station);
    virtual ~Visualization();
private:
    void CreateColors();
    void DrawFrame(int xcord, int ycord, int x, int y,int id, bool drawID);
    void DrawDistributors(int xcord, int ycord, int id);
    void MoveFrame(int xcord, int ycord, int x, int y, int id);
    void ClearFrame(int xcord, int ycord, int x, int y, int id);
    void SetDistributorStatus(int xcord, int ycord, bool status, int id);
    void Legend();
    void Rectangle(int y1, int x1, int y2, int x2);
};

#endif /* VISUALIZATION_H */

