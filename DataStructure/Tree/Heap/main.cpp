#include "maxHeap.hpp"

int main()
{
    maxHeap<int> tree(10);
    tree.push(14);
    tree.push(12);
    tree.push(7);
    tree.push(10);
    tree.push(6);
    tree.push(8);
    tree.print();
}