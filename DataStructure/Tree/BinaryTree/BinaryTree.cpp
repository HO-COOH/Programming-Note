#include <gtest/gtest.h>
#include "BinaryTreeNode.hpp"
#include <iostream>

class TreeA : public ::testing::Test
{
public:
    std::unique_ptr<BinaryTreeNode<char>> root 
    { 
        new BinaryTreeNode<char>
        {
            '+', 
            new BinaryTreeNode<char>
            {
                '*',
                new BinaryTreeNode<char>('a'),
                new BinaryTreeNode<char>('b')
            },
            new BinaryTreeNode<char>
            {
                '/',
                new BinaryTreeNode<char>('c'),
                new BinaryTreeNode<char>('d')
            }
        }
    };
};
class TreeB : public ::testing::Test
{
public:
    std::unique_ptr<BinaryTreeNode<char>> root { 
        new BinaryTreeNode<char>
        {
            '+', 
            new BinaryTreeNode<char>
            {
                '+',
                new BinaryTreeNode<char>
                {
                    '+',
                    new BinaryTreeNode<char>{'a'},
                    new BinaryTreeNode<char>{'b'}
                },
                new BinaryTreeNode<char>('c')
            },
            new BinaryTreeNode<char>{'d'}
        }
    };
};
class TreeC : public ::testing::Test
{
public:
    std::unique_ptr<BinaryTreeNode<char>> root 
    {
        new BinaryTreeNode<char>
        {
            '/', 
            new BinaryTreeNode<char>
            {
                '+',
                new BinaryTreeNode<char>
                {
                    '-',
                    nullptr,
                    new BinaryTreeNode<char>{'a'}
                },
                new BinaryTreeNode<char>
                {
                    '+',
                    new BinaryTreeNode<char>{'x'},
                    new BinaryTreeNode<char>{'y'}
                }
            },
            new BinaryTreeNode<char>
            {
                '*',
                new BinaryTreeNode<char>
                {
                    '+',
                    nullptr,
                    new BinaryTreeNode<char>{'b'}
                },
                new BinaryTreeNode<char>
                {
                    '*',
                    new BinaryTreeNode<char>{'c'},
                    new BinaryTreeNode<char>{'a'}
                }
            }
        }
    };
};

#define TestTree(X)                   \
    TEST_F(Tree##X, PreOrder)         \
    {                                 \
        PreOrder(root);               \
        std::cout << '\n';            \
    }                                 \
    TEST_F(Tree##X, InOrder)          \
    {                                 \
        InOrder(root);                \
        std::cout << '\n';            \
    }                                 \
    TEST_F(Tree##X, InOrderIterative) \
    {                                 \
        InOrderIterative(root);       \
        std::cout << '\n';\
    }\
    TEST_F(Tree##X, PostOrder) \
    {                         \
        PostOrder(root);      \
        std::cout << '\n';    \
    }\
    TEST_F(Tree##X, LevelOrder) \
    {                         \
        LevelOrder(root);      \
        std::cout << '\n';    \
    }\

TestTree(A)
TestTree(B)
TestTree(C)
