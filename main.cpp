#include "main.h"

int tick;
int x;
int y;

vector<vector<int8_t>> matrix;

void TreeClass::grow() {
    if (this->height != this->currentHeight)
    {
        this->currentHeight++;
    }
    this->currentAge++;
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matrix.assign(64, vector<int8_t>(128, 0));
    MainWindow w;
    w.show();
    tick = w.tick;
    x = w.x;
    y = w.y;

    vector<TreeClass> trees(5);

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
        while(t == randomNum) t = rand() % x;
        randomNum = t-1;
        cout << randomNum << " ";
        trees[i].root = tuple(y - 1, randomNum);
        matrix[y - 1][randomNum] = 1;
    }
    cout << endl;
    w.trees += trees.size();

    for (int i = 0; i < trees.size(); i++)
    {
        trees[i].grow();
    }
    w.tick++;

    //tree1.die();
    //w.trees = 0;

    return a.exec();
}
