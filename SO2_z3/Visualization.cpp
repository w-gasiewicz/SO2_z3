#include "Visualization.h"
#include <ncurses.h>
#include <iostream>
#include <string>

Visualization::Visualization() 
{
    initscr();
    noecho();
    curs_set(0);//hide cursor in console
    
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
    move(0,1);
    printw("Legend: ");
    move(1,1);
    printw("Press 'q' button: to stop");
    
    attron(COLOR_PAIR(6));
    move(0,35);
    printw("Visualisation: ");
    
    attron(COLOR_PAIR(6));
    move(21,35);
    printw("Queue:");
    move(22,35);
    printw("End visualisation.");
    
    DrawDistributors(2,43,1);
    
    DrawFrame(3,35,5,6,1);
    DrawFrame(3,45,5,6,3);
    DrawFrame(13,35,5,6,2);
    DrawFrame(13,45,5,6,4);  
    
    DrawDistributors(2,63,5);
    DrawFrame(3,55,5,6,5);
    DrawFrame(3,65,5,6,6);
    DrawFrame(13,55,5,6,7);
    DrawFrame(13,65,5,6,8);    
}
void Visualization :: ActualiseQueue(){
    move(21,42);
}
void Visualization :: DrawDistributors(int xcord, int ycord,int id){//function draw distributors placement
    move(xcord,ycord);
    bool printed=false;
    for(int i=0;i<19;i++){
        attron(COLOR_PAIR(1));
        printw("|");
        move(xcord+i,ycord);
        if(i>=19/2-2 && !printed){
           attron(COLOR_PAIR(6));
            auto s = std::to_string(id);
            char const *pchar = s.c_str();
            move(xcord+i,ycord-1);
            printw(pchar);
            
            s = std::to_string(id+1);
            pchar = s.c_str();
            move(xcord+i,ycord+1);
            printw(pchar);
            
            s = std::to_string(id+3);
            pchar = s.c_str();
            move(xcord+i+2,ycord-1);
            printw(pchar);
            
            s = std::to_string(id+2);
            pchar = s.c_str();
            move(xcord+i+2,ycord+1);
            printw(pchar);
            
            move(xcord+i,ycord);
            printed=true;
        }            
    }
    move(xcord+8,ycord-8);
    for(int i=0;i<18;i++){
        printw("-");
    move(xcord+8,ycord-8+i);
    }
    
}
void Visualization :: DrawFrame(int xcord, int ycord, int x, int y, int id){//function print frame
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
            if(i>=x/2 && j>=y/2-1 && !printed){//print given id in frame
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

void Visualization :: Start(){//function start visualization
    int inputChar;
    nodelay(stdscr,true);
    CreateColors();//colors initialization
    Legend();    //draw legend
    while(true)
    {
        inputChar=getch();
        if(inputChar!=113)//while user dont press q button
        {}
        else
            return;
        
        for(int i=0;i<5;i++)
        {
//            ChangeForkStatus(&philosophers[i]);
        }
    }
}
Visualization::~Visualization() {
    endwin();//close
}