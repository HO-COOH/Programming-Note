#pragma once
/**
 * @brief 二叉树的描述
 */
class BinaryTree
{
public:
    virtual ~BinaryTree();
    virtual bool empty() const;
    virtual int size() const;
    virtual void preOrder();
    virtual void inOrder();
    virtual void postOrder();
    virtual void levelOrder();
};