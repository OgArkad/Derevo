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


    TreeClass tree1;
    tree1.colorHexCode = "#239212";
    tree1.height = 8;
    tree1.width = 4;

    int rows = 3;
    int cols = 4;

    srand(time(NULL));
    for (size_t i = 0; i < 5; i++)
    {
        int randomNum = rand() % 125;
        cout << randomNum << " ";
        for (size_t i = 0; i < 64; i++)
        {
            matrix[i][randomNum] = 1;
        }
    }
    cout << "\n";

    tree1.grow();
    w.tick++;
    cout << tree1.age << endl;
    w.trees += 5;

    //tree1.die();
    //w.trees = 0;

    return a.exec();
}
