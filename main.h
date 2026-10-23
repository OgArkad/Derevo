#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <ctime>   

#include <tuple>
#include <iostream>


using namespace std;


namespace Tree{
    class TreeClass
    {
        public:
            TreeClass() {}
        std::bitset<40> binaryArray;
        int PosX;
        int PosY;
        int idTree;
    };
}

#endif // MAIN_H
