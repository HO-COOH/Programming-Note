#include <iostream>
#include <queue>    //for LevelOrder()

/*Definition of TreeNode*/
template <typename T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T>* leftChild,
        *rightChild;

    /*Constructor*/
    binaryTreeNode()
    {
        leftChild=rightChild=nullptr;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode *theLeftChild=nullptr, binaryTreeNode* theRightChild=nullptr):element(theElement), leftChild(theLeftChild), rightChild(theRightChild)
    {
    }
};

template<typename T>
class BinaryTree
{
public:
    virtual ~BinaryTree() {}
    virtual bool empty() const=0;   //return true if the tree is empty(no root node)
    virtual int size() const=0;     //return the number of nodes in the tree
    
    /*Traverse Functions, accept a function pointer*/
    // virtual void PreOrder(void (*)(T*))=0;
    // virtual void InOrder(void (*)(T*))=0;
    // virtual void PostOrder(void (*)(T*))=0;
    // virtual void LevelOrder(void (*)(T*))=0;
    virtual void PreOrder(binaryTreeNode<T>*t);
    virtual void InOrder(binaryTreeNode<T>*t);
    virtual void PostOrder(binaryTreeNode<T>*t);
};

template<typename T>
class LinkedBinaryTree:public BinaryTree<T>
{
    binaryTreeNode<T>* root=nullptr;
    int treeSize=0;
public:
    bool empty() const {return treeSize==0;}
    int size() const {return treeSize;}
    ~LinkedBinaryTree()
    {
        delete root;
    }
};


/*Traverse Functions*/
template<typename T>
void Visit(binaryTreeNode<T>* node)
{
    std::cout<<node->element<<' ';
}

template<typename T>
void BinaryTree<T>::PreOrder(binaryTreeNode<T>*t)
{
    if(t!=nullptr)
    {
        Visit(t);
        PreOrder(t->leftChild);
        PreOrder(t->rightChild);
    }
}

template<typename T>
void BinaryTree<T>::InOrder(binaryTreeNode<T>*t)
{
    if(t!=nullptr)
    {
        InOrder(t->leftChild);
        Visit(t);
        InOrder(t->rightChild);
    }
}

template<typename T>
void BinaryTree<T>::PostOrder(binaryTreeNode<T>*t)
{
    if(t!=nullptr)
    {
        PostOrder(t->leftChild);
        PostOrder(t->rightChild);
        Visit(t);
    }
}

template<typename T>
void Infix(binaryTreeNode<T>*t) //add () to a arithimetic tree
{
    using std::cout;
    if(t!=nullptr)
    {
        cout<<'(';
        Infix(t->leftChild);    //left operand
        cout<<t->element;       //operator
        Infix(t->rightChild);   //right operand
        cout<<')';
    }
}

template<typename T>
void LevelOrder(binaryTreeNode<T>*t)
{
    using namespace std;
    queue<binaryTreeNode<T>*>q;
    while(t!=nullptr)
    {
        Visit(t);
        if(t->leftChild!=nullptr)
            q.push(t->leftChild);
        if(t->rightChild!=nullptr)
            q.push(t->rightChild);
        try
        {
            t=q.front();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }
        q.pop();
    }
}


