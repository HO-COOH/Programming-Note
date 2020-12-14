#pragma once
#include "BinaryTreeNode.hpp"
/**
 * @brief 二叉树的描述
 * 
 * @tparam T 二叉树节点的类型
 */
template<class T>
class BinaryTree
{
    T* root = nullptr;
    int nodes;
public:
    ~BinaryTree();
    bool empty() const;
    int size() const;
    void preOrder(void (*)(T*)) const;//此成员函数接收一个函数作为参数，该函数参数是访问根节点所执行的操作
    void inOrder(void (*)(T*)) const;
    void postOrder(void (*)(T*)) const;
    void levelOrder(void (*)(T*)) const;
};

template<class T>
using LinkedBinaryTree = BinaryTree<BinaryTreeNode<T>>;