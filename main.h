#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>

#include "linkedlist.h"
#include "tree.h"
#include "mainwindow.h"

std::vector<std::vector<int8_t>> matrix(64, std::vector<int8_t>(128, 0)); //the main matrix (the map)
#define TREES 1 //are trees for real?
LinkedList<Tree::TreeClass> trees; //the LinkedList containing the main forest


#endif // MAIN_H
