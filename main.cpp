#include "main.h"
//inkább a .h (itt main.h) ban includolj, így átláthatóbb, és azért vannak a header fájlok...

//using namespace std; //apparently this is not too safe, when working whith lot's of imports...

std::vector<std::vector<int8_t>> matrix(64, std::vector<int8_t>(128, 0));

namespace Tree{
    int tick;
    int x;
    int y;

    void step() {}

    void reset(){
        tick = 0;
        matrix.assign(y, std::vector<int8_t>(x, 0));
        #ifdef TREES //Some crazy shii is going on here
            const int c = trees.count;
            trees.Clear();
            for (int i = 0; i <= c; i++)
            {
                trees.Push(TreeClass());
                trees.Peek().idTree = i;
                trees.PeekAt(i).posY = y - 1;
                //tre.PeekAt(i).posX = (int)(rand() % x);
            }
        #endif
        std::cout << "game reseted" << std::endl;
    }
}

#define TREES 1 //are trees real?
LinkedList<Tree::TreeClass> trees;

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand(time(NULL));

    Tree::x = w.x;
    Tree::y = w.y;
    Tree::tick = w.tick;


    for (int i = 0; i < 5; i++)
    {
        trees.Push(Tree::TreeClass());
        trees.Peek().idTree = i;
        trees.PeekAt(i).posY = Tree::y - 1;
        trees.PeekAt(i).posX = (int)(rand() % Tree::x); //eddig nem működött...
    }
    std::cout << std::to_string(trees.Peek().idTree) << std::endl;

    return a.exec();
}