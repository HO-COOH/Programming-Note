# 数据结构

## 线性表
### 数组
### 链表
#### 单链表
#### 双向链表

## 栈

## 队列

## 树

### 二叉树

### 堆

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
