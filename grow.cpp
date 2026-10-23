#include <iostream>
#include <vector>
#include <string>
#include <span>
#include "main.h"

using namespace std;

struct grow
{
    int first;
    int second;
    int third;
};

int grow(const TreeClass& tree) {
    
    std::span<const int8_t> slice(tree.genome.data() + 24, 35); 

    return 0;
}

