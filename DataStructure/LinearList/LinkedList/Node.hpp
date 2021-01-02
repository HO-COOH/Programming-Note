#pragma once

/**
 * @brief 单链表节点的定义
 * 
 * @tparam T 数据的类型
 */
template<typename T>
struct Node
{
    /*data members*/
    T element{};
    Node<T> *next = nullptr;

    /*Methods*/
    Node(const T &element)
    {
        this->element=element;
    }
    Node(const T& element, Node<T>* next)
    {
        this->element=element;
        this->next=next;
    }
};