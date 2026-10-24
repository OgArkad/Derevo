#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <ctime>

#include <tuple>
#include <iostream>
#include <bitset>

namespace Tree{
    class TreeClass
    {
        public:
            TreeClass() {}
            std::bitset<40> binaryArray;
            int PosX;
            int PosY;
            int idTree;
            //void grow();
            //void die();
    };

    void reset();
}

#endif // MAIN_H
