#include "BinaryTree.hpp"

/*Solve the booster placement problem*/
struct booster
{
    int degradeToLeaf;      //the maximum degrade from this node all the way down to the leaves
    int degradeFromParent;  //the degrade from this node to its direct parent node
    bool boosterHere=false;       //true -> a booster is placed on this node
};

std::ostream& operator<<(std::ostream& out, const booster& b)
{
    out<<"Degrade to leaf: "<<b.degradeToLeaf<<"\t Degrade from parent: "<<b.degradeFromParent<<"\t Booster? ";
    if(b.boosterHere)
        out<<"√";
    else
        out<<"X";
    out<<std::endl;
    return out;        
}

void PlaceBoosters(binaryTreeNode<booster>* x, int tolerance)
{
    x->element.degradeToLeaf=0;
    int leftDegrade, rightDegrade;
    if(binaryTreeNode<booster>* leftChild=x->leftChild) //left child is not nullptr
    {
        int degrade=leftChild->element.degradeToLeaf+leftChild->element.degradeFromParent;
        if(degrade>tolerance)   //put a booster here (the left child)
        {
            leftChild->element.boosterHere=true;
            leftDegrade=leftChild->element.degradeToLeaf;
        }
        else    //no booster is placed here
            leftDegrade=degrade;
    }
    if(binaryTreeNode<booster>* rightChild=x->rightChild) //right child is not nullptr
    {
        int degrade=rightChild->element.degradeToLeaf+rightChild->element.degradeFromParent;
        if(degrade>tolerance)   //put a booster here (the left child)
        {
            rightChild->element.boosterHere=true;
            rightDegrade=rightChild->element.degradeToLeaf;
        }
        else    //no booster is placed here
            rightDegrade=degrade;
    }
    x->element.degradeToLeaf=std::max(leftDegrade, rightDegrade);
}

int main()
{

}