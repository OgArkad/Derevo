#pragma once

#include <bitset>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <cstdint>//int_8t
#include <iostream>//cout
#include "linkedlist.h"

namespace Tree{
    class TreeClass
    {
        public:
            TreeClass() {}
            std::bitset<40> binaryArray;
            int posX;
            int posY;
            int idTree;
    };
    extern int tick;
    extern int x;
    extern int y;

    void initRandom();
    void reset();
    void step();
    void genTrees(int count);
    void growFractal(Tree::TreeClass& tree);
}

extern std::vector<std::vector<int8_t>> matrix;
extern LinkedList<Tree::TreeClass> trees;