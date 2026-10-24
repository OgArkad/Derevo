#include "main.h"
#include "mainwindow.h"
//inkább a .h (itt main.h) ban includolj, így átláthatóbb, és azért vannak a header fájlok...

using namespace std;


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
vector<TreeClass> trees(5);//le lesz cserélve

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand(time(NULL));
    LinkedList<TreeClass> tre;

    for (int i = 0; i <= trees.size(); i++)
    {
        tre.Push(TreeClass());
        tre.Peek().idTree = i;
        tre.PeekAt(i).posY = y - 1;
        //tre.PeekAt(i).posX = (int)(rand() % x);
    }

    //tree1.die();
    //w.trees = 0;
    cout << std::to_string(tre.Peek().idTree) << endl;

    return a.exec();
}