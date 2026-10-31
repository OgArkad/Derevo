#include "tree.h"

namespace Tree{//ezt igazából ki kéne rakni egy külön fájlba
    int tick = 0;
    int x = 128;
    int y = 64;

    void initRandom() {
        std::srand(time(NULL));
    }

    void genTrees(int count){//noexcept, static meaning?
        for (int i = 0; i < count; i++)
        {
            trees.Push(Tree::TreeClass());
            TreeClass& current = trees.Peek(); //itt a PeekAt(i) is működne, de ez így optimálisabb
            current.idTree = i;
            const int ty = y - 1;
            current.posY = ty;
            int tx = rand() % x;
            int j = 0;
            while (matrix[ty][tx] > 0 && j < 250){
                tx = (int)(rand() % x); //ez azért lenne, hogy ne generáljon egymásra több fát, de mégis előfordul v.miért....
                j++;
            }
            current.posX = tx;

            current.binaryArray[0] = 0;
            matrix[current.posY][current.posX] = 1;
        }
    }

    void growFractal(Tree::TreeClass& tree){
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
        for (int i = 0; i < trees.count; i++)
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
            const int treesCnt = trees.count
            trees.Clear();
            genTrees(treesCnt);
        #endif
        std::cout << "game reseted" << std::endl;
    }
}

int leavesCount(int tx, int ty){
    if (!(ty < matrix.size() && matrix.size() >= 1 && matrix[0].size() > tx)) return 0;
    if (matrix[ty][tx] == 0) return 0;
    return 1 + leavesCount(ty - 1, tx) + leavesCount(ty, tx + 1) + leavesCount(ty, tx - 1);
}