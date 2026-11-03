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
            current.binaryArray[1] = 0;
            matrix[current.posY][current.posX] = 1;
        }
    }


    void growBranch(int px, int py, int direction, int length, int depth)
    {
        if (depth <= 0 || length <= 0) return;
        for (int i = 0; i < length; i++)
        {
            if (px < 0 || px >= x || py < 0 || py >= y) return;
            matrix[py][px] = 1;
            if (direction == 0) // 0 = fel, 1 = jobb, 2 = bal
                py--;
            else if (direction == 1) {
                rand() % 50 == 0 ? py++ : py--;
                rand() % 50 == 0 ? px++ : px--;
            }
            else {
                rand() % 50 == 0 ? py++ : py--;
                rand() % 50 == 0 ? px-- : px++;
            }
        }
        growBranch(px, py, 0, length * 0.5, depth - 1);
        growBranch(px, py, 1, length * 0.4, depth - 1);
        growBranch(px, py, 2, length * 0.4, depth - 1);
    }
    int h = 1;

    void growFractal(Tree::TreeClass& tree){
       int x = tree.binaryArray.to_ulong();
       growBranch(tree.posX, tree.posY, 0, h, tree.binaryArray.to_ullong());
       tree.binaryArray = x + 1;
       if (h+1 < y*0.5) h++;
       std::cout << tree.idTree << " : " << tree.binaryArray.to_ullong() << std::endl;
    }

    /// @brief Everything that should be called in the main loop, will go here.
    void step() {
        for (int i = 0; i < trees.count; i++)
        {
            //std::cout << item.idTree << std::endl;
            /*int tx = item.grow();
            std::cout << tx << std::endl;*/
            growFractal(trees.PeekAt(i));//ezt majd cseréld le
        }
    }

    /// @brief Reset's the main matrix, clears the tree list, sets tick to 0.
    void reset(){
        tick = 0;
        matrix.assign(y, std::vector<int8_t>(x, 0));
        const int treesCnt = trees.count;
        trees.Clear();
        genTrees(treesCnt);

        std::cout << "game reseted" << std::endl;
    }
}

int leavesCount(int tx, int ty){
    if (!(ty < matrix.size() && matrix.size() >= 1 && matrix[0].size() > tx)) return 0;
    if (matrix[ty][tx] == 0) return 0;
    return 1 + leavesCount(ty - 1, tx) + leavesCount(ty, tx + 1) + leavesCount(ty, tx - 1);
}