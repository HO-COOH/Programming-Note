# 数据结构

此目录下的代码尽量与书本相同，有些小的名称上的改动是为了贴合C++命名规范。很多代码已经完全不符合现代C++编程规范，然而这不是重点，重点是学习数据结构。模仿标准库的代码可以在我的另一个[repo:Having fun/Reinvent STL](https://github.com/HO-COOH/HavingFun/tree/master/Reinvent%20STL)中找到。

## 线性表
- **线性表**又称**有序表**，它的每一个实例都是元素的一个有序集合
- 每个实例的形式为(e0, e1, ..., e(n-1))，其中n为有穷自然数
- e
```cpp
template<class T>
class LinearList
{
public:
    virtual ~LinearList();
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& operator[](int index) const = 0;
    virtual int indexOf(const T& element) const = 0;//返回element元素第一次出现时的索引
    virtual void erase(int index) = 0;              //删除索引为index的元素 
};
```
### 数组
```cpp
template<typename T>
class ArrayList: public LinearList<T>
{
protected:
    T* element;
    int capacity;
    int size;
public:
    /*...*/
};
```

### 链表
单节点的定义
```cpp
template<class T>
struct Node
{
    T element;
    Node<T>* next;
};
```
#### 单链表
```cpp
template<class T>
class List: public LinearList<T>
{
protected:
    Node<T>* first;
    int size;
public:
    /*...*/
};
```
#### 单向循环链表
在单链表的最前面增加一个节点成为头节点，将尾节点与头节点连起来便成为单向循环链表
```cpp
template<class T>
class CircularList
{

};
```
#### 双向链表
```cpp
template<class T>
struct DoublyLinkedNode
{
    T element;
    DoublyLinkedNode<T>* previous, next;
};

template<class T>
class DoublyLinkedList: public LinearList<T>
{
protected:
    DoublyLinkedNode<T>* first;
    int size;
};
```
## 栈

## 队列

## 树
- 一棵树t是一个非空的有限元素的集合，其中的一个元素称为**根**，其余的元素（如果有的话）组成t的**子树**
- 树中没有孩子的元素称为**叶子**
- 树根是1级，其孩子（如果有）是2级，孩子的孩子是3级
- 一棵树的**高度/深度**是树中级的个数
- 一个元素的**度**是指其孩子的个数
- 一棵树的**度**是其元素的度的最大值

### 二叉树
- 一棵二叉树t是有限个元素的集合，当二叉树非空时，其中一个元素称为**根**，余下的元素（如果有的话）被划分为两棵二叉树，分别为**左子树**和**右子树**
- 二叉树的每个元素都恰好又两棵子树（可能为空），而树的每个元素可以有任意数量的子树
- 二叉树中每个元素的子树都是有序的，也就是有左子树和右子树之分，而树的子树是无序的
- 如果一棵二叉树有n个元素（n>0），则有(n-1)条边
  ```
  证明：
    ∵二叉树除了根节点外的每个节点有且只有一个父节点，节点与其父节点有且只有一条边，这样的节点有(n-1)个，而根节点没有父节点
    ∴共有(n-1)条边
  ```
- 如果一棵二叉树的高度为h（h>=0），则最少有h个元素，最多有(2^h - 1)个元素
  ```
  证明：
    ∵每级至少有1个元素
    ∴h级至少有h个元素
    ∵第i级最多有2^(i-1)个元素
    ∴h级最多有Sum(2^0 + 2^1 +...+2^(h-1))=2^h - 1个元素
  ```
- 如果一棵二叉树有n个元素（n>0）则它的高度最大为n，最小为ceil(log2(n+1))
  ```
  证明：
    ∵每级至少有1个元素
    ∴最大高度为n
    ∵高度为h的二叉树最多有(2^h - 1)个元素
    ∴n<=(2^h - 1), h>=log2(n+1)
    又∵h为整数
    ∴h>=ceil(log2(n+1))
  ```
- 当高度为h的二叉树恰好有(2^h - 1)个元素时，称为**满二叉树**
- 将满二叉树按从第一层到最后一层，每一层从左到右编号，从1->(2^h - 1)，按编号从大到小的顺序删除k个元素，得到**完全二叉树**
- 所以满二叉树是完全二叉树
- 若完全二叉树的编号是1<=i<=n，则下面的特性成立：
  - 如果i=1，则该元素为根，若i>1，则其父节点的编号为floor(i/2)
  - 如果2i>n，则该元素无左孩子，否则其左孩子的编号为2i
  - 如果2i+1>n，则该元素无右孩子，否则其右孩子的编号为2i+1

```cpp
template<class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T>* leftChild, *rightChild;
};
```
#### 二叉树的遍历
按根节点与左右子树的访问顺序可以分为：
- 前序  preOrder
- 中序  inOrder
- 后序  postOrder
```cpp
template<class T>
class BinaryTree
{
    T* root;
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
```
## 优先级队列
- 是0个或多个元素的集合，每个元素都有一个优先权或值
- 在**最小优先级队列**中，查找和删除的元素都是优先级最小的元素
- 在**最大优先级队列**中，查找和删除的元素都是优先级最大的元素
- 优先级队列的元素可以有相同的优先级，查找和删除按任意顺序处理
### 堆
- 一棵**大根树（小根树）**是这样一棵树，其中每个节点的值都大于（小于）等于其子节点（如果有的话），节点的子节点个数不限
- 一棵**大根树（小根数）**是完全二叉树
- 

### 竞赛树

### 搜索树

### AVL树

### 红黑树

## 图
### 概念
- 图：是一个用线和边连接在一起的顶点的集合，是有限集V、E的有序对，即G=(V, E), 其中V称为**顶点**， E成为**边**
- 每一条边连接两个顶点，用元组(i, j)表示，其中i，j为该边所连接的两个顶点
- 带方向的边称为**有向边**，不带方向的边称为**无向边**
- 当且仅当(i, j)是图的边时，称顶点i和j是**邻接的**，称边(i, j)**关联于**顶点i、j
- 如果图的所有边都是无向边，称为**无向图**
- 无向图中，与一个顶点i相关联的边的数量称为该顶点的**度**
- 一个具有n个顶点和n(n-1)/2条边的无向图，称为**完全图**
- 一个顶点序列i1, i2, ..., ik，当对每一个1<=j<=k，(ij, i(j+1))是图G的边时，称为从i1到ik的一个路径
- 一个路径，如果除了第一个（起点）和最后一个顶点（终点）之外其余顶点均不相同，那么称为一个**简单路径**
- 如果图的每对顶点间都有一条路径，称为**连通图**
- 一个起点和终点相同的简单路径称为**环路**
- 没有环路的连通无向图称为**树**
- 如果图H的顶点和边都是G的顶点和边的子集，称H时G的**子图**
- 如果G的一个子图包含G的所有顶点，而且是一棵树，称为G的**生成树**
### 程序
```
class Graph
{
property:
    Vertices
    Edges
method:
    numberOfVertices()
    numberOfEdges()
    existEdge(i, j)
    insertEdge(edge)
    eraseEdge(i, j)
    degree(i)    
}
```
```cpp
template<typename T>
class Graph
{
public:
    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existsEdge(int, int) const = 0;
    virtual void insertEdge(Edge edge) = 0;
    virtual void eraseEdge(int, int) = 0;
    virtual void degree(int) const = 0;
};
```
4种图都继承与图抽象基类：
- 无权无向图
- 加权无向图
- 无权有向图
- 加权有向图

每种图都可以用以下3种数据结构来描述：
- 邻接矩阵
- 邻接链表
- 邻接数组
