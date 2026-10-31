#include "main.h"
//inkább a .h (itt main.h) ban includolj, így átláthatóbb, és azért vannak a header fájlok.

//using namespace std; apparently this is not too safe, when working whith multiple imports...

std::vector<std::vector<int8_t>> matrix(64, std::vector<int8_t>(128, 0)); //the main matrix (the map)
#define TREES 1 //are trees for real?
LinkedList<Tree::TreeClass> trees; //the LinkedList containing the main forest

namespace Tree{
    int tick;
    int x;
    int y;

    void genTrees(int count){//noexcept, static meaning?
        for (int i = 0; i < count; i++)
        {
            trees.Push(Tree::TreeClass());
            trees.Peek().idTree = i;
            const int ty = Tree::y - 1;
            trees.Peek().posY = ty; //itt a PeekAt(i) is működne, de ez így optimálisabb
            int tx = (int)(rand() % (Tree::x - 1));// 0-1 -> 0-127
            while (matrix[ty][tx] > 0) tx = (int)(rand() % (Tree::x -1)); //ez azért lenne, hogy ne generáljon egymásra több fát, de mégi előfordul v.miért....
            trees.Peek().posX = tx;

            trees.Peek().binaryArray[0] = 0;
            matrix[trees.Peek().posY][trees.Peek().posX] = 1;
        }
    }

    void growFractal(Tree::TreeClass tree){
            if (tree.binaryArray[0] == 0){
                if (tree.posY > 0)
                    tree.posY--;
                tree.binaryArray[0] = 1;
            }
            else{
                if (tree.posX > 0)
                    tree.posX--;
                tree.binaryArray[0] = 0;
            }
            matrix[tree.posY][tree.posX] = 1;
        }

    /// @brief Everything that should be called in the main loop, will go here.
    void step() {
        for (int16_t i = 0; i < trees.count; i++)
        {
            //std::cout << item.idTree << std::endl;
            /*int tx = item.grow();
            std::cout << tx << std::endl;*/
            growFractal(trees.PeekAt(i));
        }
    }

    /// @brief Reset's the main matrix, clears the tree list, sets tick to 0.
    void reset(){
        tick = 0;
        matrix.assign(y, std::vector<int8_t>(x, 0));
        #ifdef TREES //Some crazy shii is going on here
            genTrees(trees.count);
        #endif
        std::cout << "game reseted" << std::endl;
    }
}

#include "mainwindow.h"

int leavesCount(int tx, int ty){
    if (!(ty < matrix.size() && matrix.size() >= 1 && matrix[0].size() > tx)) return 0;
    if (matrix[ty][tx] = 0) return 0;
    return 1 + leavesCount(ty - 1, tx) + leavesCount(ty, tx + 1) + leavesCount(ty, tx - 1);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand(time(NULL));

    Tree::x = w.x;
    Tree::y = w.y;
    Tree::tick = w.tick;

    Tree::genTrees(5);

    std::cout << std::to_string(trees.Peek().idTree) << std::endl;

    //std::cout << leavesCount(trees.Peek().posX, trees.Peek().posX) << std::endl;
    w.appendDebug(std::to_string(leavesCount(trees.Peek().posX, trees.Peek().posX)));
    w.appendDebug(std::to_string(trees.Peek().posX) + ", " + std::to_string(trees.Peek().posY));
    return a.exec();
}