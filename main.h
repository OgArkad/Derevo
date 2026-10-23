#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <ctime>   // Добавлено для time(NULL)

#include <tuple>
#include <iostream>


using namespace std;


namespace Tree{
    class TreeClass
    {
        public:
            TreeClass() {}
            string colorHexCode = "#239212";
            int currentAge = 0;

            int height = 0;
            int width = 0;
            int currentHeight = 0;
            tuple<int, int> root;
            void grow();
            void die();
        private:
            int energy = 0;
            int age = 0;
            int roots = 0;
    };
}

#endif // MAIN_H
