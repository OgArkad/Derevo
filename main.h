#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <ctime>

#include <tuple>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstdlib>
#include "linkedlist.h"

namespace Tree{
    class TreeClass
    {
        public:
            TreeClass() {}
            std::bitset<40> binaryArray;
            int posX;
            int posY;
            int idTree;
            //void grow();
            //void die();
    };

    void reset();
}

#endif // MAIN_H
