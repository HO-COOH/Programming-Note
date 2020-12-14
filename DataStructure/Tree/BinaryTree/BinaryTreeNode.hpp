#pragma once

/**
 * @brief 二叉树节点的描述
 * 
 * @tparam T 节点元素的数据类型
 */
template<class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T>* leftChild, *rightChild;
};