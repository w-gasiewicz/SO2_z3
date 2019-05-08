#ifndef VISUALIZATION_H
#define VISUALIZATION_H

class Visualization {    
public:
    Visualization();
    void Start();
    virtual ~Visualization();
private:
    void CreateColors();
    void DrawFrame(int xcord, int ycord, int x, int y,int id);
    void DrawDistributors(int xcord, int ycord, int id);
    void  ActualiseQueue();
    void Legend();
};

#endif /* VISUALIZATION_H */

