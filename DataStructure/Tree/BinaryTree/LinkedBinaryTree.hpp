#pragma once
#include "BinaryTree.hpp"
#include "BinaryTreeNode.hpp"
#include <queue>

template<class T>
class LinkedBinaryTree:public BinaryTree
{
    /*数据成员*/
    std::unique_ptr<BinaryTreeNode<T>> root = nullptr;  //根节点
    void (*visit)(BinaryTreeNode<T> *) = ::visit;       //访问函数，默认为打印该节点的值
    int treeSize = 0;                                   //节点个数

    /*帮助函数*/
    static void PreOrderImpl(std::unique_ptr<BinaryTreeNode<T>> const& node)
    {
        if(node)
        {
            visit(node.get());
            PreOrderImpl(node->leftChild);
            PreOrderImpl(node->rightChild);
        }
    }

    static void InOrderImpl(std::unique_ptr<BinaryTreeNode<T>> const& node)
    {
        if(node)
        {
            InOrderImpl(node->leftChild);
            visit(node.get());
            InOrderImpl(node->rightChild);
        }
    }


    static void PostOrderImpl(std::unique_ptr<BinaryTreeNode<T>> const& node)
    {
        if(node)
        {
            visit(node.get());
            PostOrderImpl(node->leftChild);
            PostOrderImpl(node->rightChild);
        }
    }

    static void LevelOrderImpl(std::unique_ptr<BinaryTreeNode<T>> const &node)
    {
        std::queue<BinaryTreeNode<T>*> queue;
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

    static int HeightImpl(std::unique_ptr<BinaryTreeNode<T>> const& node)
    {
        if(!node)
            return 0;
        auto const leftHeight = HeightImpl(node->leftChild);
        auto const rightHeight = HeightImpl(node->rightChild);
        return std::max(++leftHeight, ++rightHeight);
    }

public:
    /*继承自BinaryTree的函数*/
    bool empty() const override { return treeSize == 0; }
    int size() const override { return treeSize; }
    void preOrder() override
    {
        if(root)
            PreOrderImpl(root);
    }

    void inOrder() override
    {
        if(root)
            InOrderImpl(root);
    }

    void postOrder() override
    {
        if(root)
            PostOrderImpl(root);
    }

    void levelOrder() override
    {
        if(root)
            LevelOrderImpl(root);
    }

    /*LinkedBinaryTree类的新函数*/
    /**
     * @brief 设置节点的新访问函数
     * 
     * @param func 节点的访问函数，函数应该接受一个BinaryTreeNode<T>的指针并返回void
     */
    void setVisit(void (*func)(BinaryTreeNode<T>*))
    {
        visit = func;
    }

    /**
     * @brief 返回二叉树的高度
     */
    int height() const
    {
        if(root)
            return HeightImpl(node);
    }


};