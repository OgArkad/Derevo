#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Tree::initRandom();

    Tree::x = w.x;
    Tree::y = w.y;
    Tree::tick = w.tick;

    Tree::genTrees(5);

    std::cout << std::to_string(trees.Peek().idTree) << std::endl;

    //std::cout << leavesCount(trees.Peek().posX, trees.Peek().posX) << std::endl;
    //w.appendDebug(std::to_string(leavesCount(trees.Peek().posX, trees.Peek().posX)));
    //w.appendDebug(std::to_string(trees.Peek().posX) + ", " + std::to_string(trees.Peek().posY));
    return a.exec();
}
