#include "main.h"
#include "mainwindow.h" //piszkosul circular-dependency

vector<vector<int8_t>> matrix(64, vector<int8_t>(128, 0));

namespace Tree{
    int tick;
    int x;
    int y;

    void TreeClass::grow() {
        if (this->height != this->currentHeight)
        {
            this->currentHeight++;
            if (get<1>(this->root) > 0)
                get<1>(this->root)--;
            matrix[get<1>(this->root)][get<0>(this->root)] = 1;
        }
        this->currentAge++;
        cout << "grown" << get<1>(this->root) << endl;
    }

    void TreeClass::die(){
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t z = 0; z < matrix[i].size(); z++)
            {
                if (matrix[i][z] == 1) matrix[i][z] = 0;
            }
        }
    }

}

using namespace Tree;
vector<TreeClass> trees(5);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//Shift + Tab => remove 1 tab to the left
    MainWindow w;
    w.show();
    tick = w.tick;
    x = w.x;
    y = w.y;

    for (int i = 0; i < trees.size(); i++)
    {
        trees[i].height = 8;
        trees[i].width = 4;
    }
    int rows = 3;
    int cols = 4;

    srand(time(NULL));
    int randomNum;
    for (size_t i = 0; i < trees.size(); i++)
    {
        int t =  rand() % x;
        while(t == randomNum) t = rand() % (x-1);
        randomNum = t;
        trees[i].root = tuple(randomNum, y - 1);
        matrix[y - 1][randomNum] = 1;
    }

    for (int i = 0; i < trees.size(); i++)
    {
        trees[i].grow();
    }
    w.tick++;

    //tree1.die();
    //w.trees = 0;

    return a.exec();
}

