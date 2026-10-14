#include <QApplication>
#include <ctime>   // Добавлено для time(NULL)
#include <cstdint>
#include "mainwindow.h"

int tick;
int x;
int y;

vector<vector<int8_t>> matrix;

class TreeClass {
public:
    string colorHexCode;
    int height = 0;
    int width = 0;
    int currentHeight = 0;
    int roots = 0;
    int energy = 0;
    int age = 0;
    int currentAge = 0;
};

void grow(TreeClass &tree) {
    if (tree.height != tree.currentHeight)
    {
        tree.currentHeight++;
    }
    tree.currentAge++;
}

void die(TreeClass &tree){
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t z = 0; z < matrix[i].size(); z++)
        {
            if (matrix[i][z] == 1)
            {
                matrix[i][z] = 0;
            }
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

    for (size_t i = 0; i < y; i++)
    {
        for (size_t z = 0; z < x; z++)
        {
            cout << to_string(matrix[i][z]);
        }
        cout << "\n";
    }

    cout << "\nDone" << endl;

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

    for (size_t i = 0; i < y; i++)
    {
        for (size_t z = 0; z < x; z++)
        {
            cout << to_string(matrix[i][z]);
        }
         cout << "\n";
    }

    grow(tree1);
    w.trees++;

    die(tree1);
    w.trees--;

    return a.exec();
}
