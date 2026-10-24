#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <QApplication>
#include "main.h"
#include "mainwindow.h" 

using namespace std;

int tick;
int x;
int y;
vector<vector<int8_t>> matrix(64, vector<int8_t>(128, 0));

namespace Tree{
    int tick;
    int x;
    int y;

    /*void TreeClass::grow() {
        if (this->height != this->currentHeight)
        {
            this->currentHeight++;
            if (get<1>(this->root) > 0)
                get<1>(this->root)--;
            matrix[get<1>(this->root)][get<0>(this->root)]++;
        }
        int random = (y-1) - (rand() % currentHeight);
        cout << random << ". " << endl;
        matrix[random][((int)(get<0>(this->root) + ((rand() % 10) > 5 ? +this->width : -this->width)))]++;
        cout << ((int)(get<0>(this->root) + ((rand() % 10) > 5 ? +1 : -1))) << endl;
        this->currentAge++;
        this->height += 0.25;
    }

    void TreeClass::die(){
        while (get<1>(this->root) < y){
            matrix[get<1>(this->root)++][get<0>(this->root)] = 0;
        }
    }*/

    void reset(){
        tick = 0;
        matrix.assign(y, vector<int8_t>(x, 0));
        trees.assign(trees.size(), TreeClass());
    }
}

using namespace Tree;
vector<TreeClass> trees(5);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //tick = w.tick;
    //x = w.x;
    //y = w.y;

    /*for (int i = 0; i < trees.size(); i++)
    {
        trees[i].height = 8;
        trees[i].width = 4;
    }*/

    srand(time(NULL));
    int randomNum = -1;
    /*for (size_t i = 0; i < trees.size(); i++)
    {
        int t = rand() % (x-1);
        while(t == randomNum) t = rand() % (x - 1);
        randomNum = t;
        trees[i].root = tuple(randomNum, y - 1);
        matrix[y - 1][randomNum] = 1;
    }*/

    //tree1.die();
    //w.trees = 0;

    return a.exec();
}