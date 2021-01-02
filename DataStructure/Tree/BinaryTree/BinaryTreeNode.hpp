#pragma once

#include <memory>
/**
 * @brief 二叉树节点的描述
 * 
 * @tparam T 节点元素的数据类型
 */
template<class T>
struct BinaryTreeNode
{
    T element;
    std::unique_ptr<BinaryTreeNode<T>> leftChild, rightChild;

    BinaryTreeNode(T value) : element{std::move(value)}, leftChild{nullptr}, rightChild{nullptr} {}
    BinaryTreeNode(T value, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right) : element{std::move(value)}, leftChild{left}, rightChild{right} {}
    BinaryTreeNode(T value, std::unique_ptr<BinaryTreeNode<T>> left, std::unique_ptr<BinaryTreeNode<T>> right) : element{std::move(value)}, leftChild{std::move(left)}, rightChild{std::move(right)} {}
};

#include <iostream>
template<typename BinaryTreeNode>
void visit(BinaryTreeNode* node)
{
    std::cout << node->element << ' ';
}


template<typename T>
void PreOrder(std::unique_ptr<BinaryTreeNode<T>> const& node)
{
    if(node)
    {
        visit(node.get());
        PreOrder(node->leftChild);
        PreOrder(node->rightChild);
    }
}

template<typename T>
void InOrder(std::unique_ptr<BinaryTreeNode<T>> const& node)
{
    if(node)
    {
        InOrder(node->leftChild);
        visit(node.get());
        InOrder(node->rightChild);
    }
}

#include <stack>
template<typename T>
void InOrderIterative(std::unique_ptr<BinaryTreeNode<T>> const& node)
{
    std::stack<BinaryTreeNode<T> *> s;
    auto current = node.get();
    while (!s.empty() || current)
    {
        while(current)
        {
            s.push(current);
            current = current->leftChild.get();
        }
        //循环退出时左子树已经遍历完毕，current是一个空的指针，s.top()是current的父节点
        visit(s.top()); //访问这个节点
        //让current指向这个父节点的右子树
        current = s.top()->rightChild.get();
        s.pop();
    }
}

template<typename T>
void PostOrder(std::unique_ptr<BinaryTreeNode<T>> const& node)
{
    if(node)
    {
        visit(node.get());
        PostOrder(node->leftChild);
        PostOrder(node->rightChild);
    }
}

#include <queue>
template<typename T>
void LevelOrder(std::unique_ptr<BinaryTreeNode<T>> const& node)
{
    std::queue<BinaryTreeNode<T>*> queue;
    if(node)
        queue.push(node.get());
    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        visit(current);
        if(current->leftChild)
            queue.push(current->leftChild.get());
        if(current->rightChild)
            queue.push(current->rightChild.get());
    }
}