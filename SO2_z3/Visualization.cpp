#include "Visualization.h"
#include "Client.h"
#include "Distributor.h"
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <valarray>
Visualization::Visualization() 
{
    initscr();
    noecho();
    curs_set(0);//hide cursor in console
    resizeterm(90,255);
}
void Visualization::CreateColors() 
{
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);   
    init_pair(4, COLOR_CYAN, COLOR_BLACK);   
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);   
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}
void Visualization::Legend(){
    attron(COLOR_PAIR(6));
    mvprintw(0,1,"Legend: ");
    mvprintw(1,1,"Press 'q' button: to stop");
    attron(COLOR_PAIR(3));
    mvprintw(2,1,"0 ");
    attron(COLOR_PAIR(1));
    mvprintw(2,3," - distributor/sales man busy.");
    attron(COLOR_PAIR(2));
    mvprintw(3,1,"0 ");
    attron(COLOR_PAIR(1));
    mvprintw(3,3," - distributor/sales man free.");
    attron(COLOR_PAIR(4));
    mvprintw(1,35,"GASOLINE STATION:");
    
    attron(COLOR_PAIR(6));
    mvprintw(20,15,"Queue:");
    
    //border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 0, 0, 0, 0);
    DrawDistributors(2,43,1);  //draw first 4 distributors      
    DrawDistributors(2,63,5);
    
    //printf carwash
    attron(COLOR_PAIR(4));
    mvprintw(1,85,"CAR WASH:");
    DrawFrame(3,85,5,12,0,false);   
    
    attron(COLOR_PAIR(6));
    mvprintw(8,85,"Queue:");
    
    //printf payment place
    attron(COLOR_PAIR(4));
    mvprintw(12,85,"PAYMENT PLACE:");
    DrawFrame(13,85,5,12,0,false);
    //hline(ASC_BLOCK,15);
    attron(COLOR_PAIR(6));
    mvprintw(18,85,"Queue:");
}
void Visualization :: ActualiseQueue(){
    move(21,42);
}
void Visualization :: SetDistributorStatus(int xcord, int ycord, bool status,int id){   
        auto s = std::to_string(id);
        char const *pchar = s.c_str();
    if(status){
        attron(COLOR_PAIR(3));
        mvprintw(xcord,ycord,pchar);  
    }
    else{
        attron(COLOR_PAIR(2));
        mvprintw(xcord,ycord,pchar);
    }
}
void Visualization :: DrawDistributors(int xcord, int ycord,int id){//function draw distributors placement
    move(xcord,ycord);
    bool printed=false;
    for(int i=0;i<19;i++){
        attron(COLOR_PAIR(1));
        printw("|");
        move(xcord+i,ycord);        
    }
    move(xcord+8,ycord-8);
    for(int i=0;i<18;i++){
        printw("-");
        move(xcord+8,ycord-8+i);
    }    
}
void Visualization:: MoveFrame(int xcord, int ycord, int x, int y, int id){
    move(xcord,ycord);
    for(int k=1;k<6;k++){
    for(int i=0; i<= x;i++){
        for(int j=0; j<= y; j++){      
                printw(" ");
                move(xcord+i,ycord+j+1);
        }                
            move(xcord+i,ycord);
    }
       xcord-=1;
       DrawFrame(xcord,ycord,x,y,id,true);
       std::this_thread::sleep_for(std::chrono::milliseconds(250));//sleep for 250 ms.
       refresh();//refresh console
    }
}
void Visualization :: DrawFrame(int xcord, int ycord, int x, int y, int id, bool drawID){//function print frame
    move(xcord,ycord);
    bool printed=false;
    for(int i=0; i<= x;i++){
        attron(COLOR_PAIR(5));
        for(int j=0; j<= y; j++){
            attron(COLOR_PAIR(5));
            if (i == 0 || i == x || j == 0 || j == y)       
                printw("*");
            else                
                move(xcord+i,ycord+j+1);
            if(drawID && i>=x/2 && j>=y/2-1 && !printed){//print given id in frame
                printw(" ");                
                move(xcord+i,ycord+j);
                attron(COLOR_PAIR(6));
                auto s = std::to_string(id);
                char const *pchar = s.c_str();
                printw(pchar);
                printed=true;
            }
        }                
            move(xcord+i,ycord);
    }
}
void Visualization :: ClearFrame(int xcord, int ycord, int x, int y, int id){
     move(xcord,ycord);
    for(int i=0; i<= x;i++){
        for(int j=0; j<= y; j++){
                printw(" ");
            }
            move(xcord+i,ycord);
        }                
}
void Visualization :: SetQueue(int xcord, int ycord,int id){
        DrawFrame(xcord,ycord,5,6,id,true);
}
void Visualization :: Start(Client clients[],Distributor distributors[], SalesMan salesmans[], vector<int> & gasolineQueue,vector<int> & paymentQueue){//function start visualization
    int inputChar;
    int xcar[8]={3,3,13,13,3,3,13,13};
    int ycar[8]={35,45,35,45,55,65,55,65};
    nodelay(stdscr,true);
    CreateColors();//colors initialization  
    //initialize distributor and salesmens starting status status
    for(int i=0;i<8;i++){
        SetDistributorStatus(distributors[i].xcord,distributors[i].ycord,false,distributors[i].id);
    }
    for(int i=0;i<4;i++){
        SetDistributorStatus(salesmans[i].xcord,salesmans[i].ycord,salesmans[i].isWorking,salesmans[i].id);
    }
    Legend();    //draw legend
    while(true)
    {
        inputChar=getch();
        if(inputChar!=113){//while user dont press q button
        }
        else
            return;    
        //######################################GASOLINE MAINTANCE########################################################################
        int ycord=21;        
            for(int i=0;i<gasolineQueue.capacity()+1;i++){//clear gasoline queue           
                ClearFrame(20,ycord,5,6,clients[gasolineQueue[i]].id);
                ycord+=8;
            }
            for(int i=0;i<8;i++){
                SetDistributorStatus(distributors[i].xcord,distributors[i].ycord,distributors[i].isUsed,distributors[i].id);
                if(distributors[i].isUsed)
                    DrawFrame(xcar[i],ycar[i],5,6,distributors[i].clientID,true);
                else           
                    ClearFrame(xcar[i],ycar[i],5,6,distributors[i].clientID);
            }      
        ycord=21;
            for(int i=0;i<gasolineQueue.size();i++){      //actualise gasoline queue     
                ClearFrame(20,ycord,5,6,clients[gasolineQueue[i]].id);
                DrawFrame(20,ycord,5,6,clients[gasolineQueue[i]].id,true);
                ycord+=8;
                ClearFrame(20,ycord,5,6,clients[gasolineQueue[i]].id);
            } 
        //######################################PAYMENT MAINTANCE########################################################################
         ycord=86;
         for(int i=0;i<11;i++){
                mvprintw(16,ycord," ");
                ycord+=1;
        }
        ycord=86;
         for(int i=0;i<4;i++){//actualise salesmans status
            SetDistributorStatus(salesmans[i].xcord,salesmans[i].ycord,salesmans[i].isWorking,salesmans[i].id);
            if(salesmans[i].isWorking){
                attron(COLOR_PAIR(1));
                auto s = std::to_string(salesmans[i].clientID);
                char const *pchar = s.c_str();
                mvprintw(16,ycord,pchar);
            }
            ycord+=3;
        }
        ycord=91;
        for(int i=0;i<32;i++){//clear payment place queue
                mvprintw(18,ycord," ");
                ycord+=1;
        }
        ycord=91;
        for(int i=0;i<paymentQueue.size();i++){//for(int i=0;i<15;i++){//print payment place queue
            if(clients[paymentQueue[i]].waitToPay){   
                attron(COLOR_PAIR(1));
                auto s = std::to_string(clients[paymentQueue[i]].id);
                char const *pchar = s.c_str();
                printw("|");
                mvprintw(18,ycord,pchar);
                printw("|");
                ycord+=3;
            }
        }
    }
}
Visualization::~Visualization() {
    endwin();//close
}