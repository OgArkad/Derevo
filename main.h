#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <ctime>   // Добавлено для time(NULL)
#include <cstdint>
#include "mainwindow.h"


class TreeClass
{
public:
    TreeClass() {}
    string colorHexCode;

    int energy = 0;
    int age = 0;
    int currentAge = 0;

    int height = 0;
    int width = 0;
    int currentHeight = 0;
    int roots = 0;

    void grow();
    void die();

};

#endif // MAIN_H
