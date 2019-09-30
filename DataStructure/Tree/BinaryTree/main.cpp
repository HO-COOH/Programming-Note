#include <iostream>
#include <queue>    //for LevelOrder()
#include <array>

/*Definition of TreeNode*/
template <typename T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild = nullptr, * rightChild = nullptr;

	/*Constructor*/
	binaryTreeNode() = default;
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild = nullptr, binaryTreeNode* theRightChild = nullptr) :element(theElement), leftChild(theLeftChild), rightChild(theRightChild)
	{}
};

/*Traverse Functions*/
//print the element of the node
template<typename T>
void Visit(binaryTreeNode<T>* node)
{
	std::cout << node->element << ' ';
}

template<typename T>
void PreOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		Visit(t);
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}

template<typename T>
void InOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		InOrder(t->leftChild);
		Visit(t);
		InOrder(t->rightChild);
	}
}

template<typename T>
void PostOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		PostOrder(t->leftChild);
		PostOrder(t->rightChild);
		Visit(t);
	}
}

template<typename T>
void LevelOrder(binaryTreeNode<T>* t)
{
	using namespace std;
	queue<binaryTreeNode<T>*>q;
	while (t != nullptr)
	{
		Visit(t);
		if (t->leftChild != nullptr)
			q.push(t->leftChild);
		if (t->rightChild != nullptr)
			q.push(t->rightChild);
		try
		{
			t = q.front();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return;
		}
		q.pop();
	}
}

/*Print the oprands in the tree with complete parathesis*/
template<typename T>
void Infix(binaryTreeNode<T>* t) //add () to a arithimetic tree
{
	using std::cout;
	if (t != nullptr)
	{
		cout << '(';
		Infix(t->leftChild);    //left operand
		cout << t->element;       //operator
		Infix(t->rightChild);   //right operand
		cout << ')';
	}
}


template<typename T>
class BinaryTree
{
public:
	virtual ~BinaryTree() {}
	virtual bool empty() const = 0;   //return true if the tree is empty(no root node)
	virtual int size() const = 0;     //return the number of nodes in the tree

	/*Traverse Functions, accept a function pointer*/
	virtual void PreOrder() = 0;
	virtual void InOrder() = 0;
	virtual void PostOrder() = 0;
	virtual void LevelOrder() = 0;

};

template<typename T>
class LinkedBinaryTree :public BinaryTree<binaryTreeNode<T>>
{
	binaryTreeNode<T>* root = nullptr;
	int treeSize = 0;     //number of nodes the tree contains
	static void (*visit)(binaryTreeNode<T>*);
public:
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	LinkedBinaryTree<T>& operator<<(T element);
	template<int SIZE>
	LinkedBinaryTree<T>& operator<<(std::array<T, SIZE> arr);
	void PreOrder();
	void InOrder();
	void PostOrder();
	void Infix() { ::Infix(root); }
	void LevelOrder();
	~LinkedBinaryTree()
	{
		delete root;
	}
};

template<typename T>
void (*LinkedBinaryTree<T>::visit)(binaryTreeNode<T>*) = ::Visit;

template<typename T>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator<<(T element)
{
	std::queue<binaryTreeNode<T>*>queue;
	if (root == nullptr)
		root = new binaryTreeNode<T>(element);
	else
	{
		queue.push(root);
		while (queue.front()->leftChild != nullptr && queue.front()->rightChild != nullptr)
		{
			queue.push(queue.front()->leftChild);
			queue.push(queue.front()->rightChild);
			queue.pop();
		}
		if (queue.front()->leftChild == nullptr)
			queue.front()->leftChild = new binaryTreeNode<T>(element);
		else
			queue.front()->rightChild = new binaryTreeNode<T>(element);
	}
	return *this;
}

template<typename T>
void LinkedBinaryTree<T>::PreOrder()
{
	if (root != nullptr)
	{
		visit(root);
		::PreOrder(root->leftChild);		//calls the private function
		::PreOrder(root->rightChild);
	}
}

template<typename T>
void LinkedBinaryTree<T>::InOrder()
{
	if (root != nullptr)
	{
		::InOrder(root->leftChild);		//calls the private function
		visit(root);
		::InOrder(root->rightChild);
	}
}

template<typename T>
void LinkedBinaryTree<T>::PostOrder()
{
	if (root != nullptr)
	{
		::PostOrder(root->leftChild);
		::PostOrder(root->rightChild);
		visit(root);
	}
}

template<typename T>
template<int SIZE>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator<<(std::array<T, SIZE> arr)
{
	for (auto& element : arr)
		this->operator<<(element);
	return *this;
}

template<typename T>
void LinkedBinaryTree<T>::LevelOrder()
{

}

int main()
{
	LinkedBinaryTree<char> tree2;
	tree2 << std::array{ '+','*','/','a','b','c','d' };
	tree2.Infix();
}
