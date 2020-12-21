#pragma once
#include <iterator>
#include <iostream>
#include <algorithm>
#include <stdexcept>

/*Abstract class of LinearList*/
#include "../LinearList.hpp"

/*Definition of Array*/
template <typename T>
class ArrayList : public LinearList<T>
{
protected:
    T *elements;                      //data
    int m_capacity;                   //capacity of the Array
    int m_size;                       //number of elements in the Array
    int const m_increaseSize;         //练习4新增
    
    /**
     * @brief 检查下标是否越界，范围必须是(0, m_size]之间
     * 
     * @throw 下标越界时抛出std::out_of_range
     */
    void indexCheck(int index) const;

    /**
     * @brief 改变数组大小
     * 
     * @param newLength 数组的新大小，必须是非负整数
     * @throw 如果不是，throw std::bad_array_new_length
     */
    void changeLength(int newLength);

public:
    /**
     * @brief 构造时预分配初始容量
     * 
     * @param initialCapacity 初始容量
     */
    ArrayList(int initialCapacity = 10);
    
    /**
     * @brief 允许构造时指定数组空间满时数组长度的增加量
     * 
     * @param increaseWhenFull 数组空间满时数组长度的增加量
     * @param initialCapacity 构造时预分配的内存大小
     */
    ArrayList(int increaseWhenFull, int initialCapacity);

    //复制构造函数
    ArrayList(const ArrayList<T> &);

    //析构函数
    ~ArrayList() { delete[] elements; }

    //继承自LinearList类的方法

    /**
     * @brief Return whether the linear list is empty
     */
    bool empty() const override { return m_size == 0; }

    /**
     * @brief Return the number of elements in the linear list
     */
    int size() const override { return m_size; }

    /**
     * @brief Get the element at i-th index
     * 
     * @param index Index of the element
     * @return T& A reference to the elements
     */
    T &get(int index) const override;

    /**
     * @brief Get the index of an element first appeared in the linear list, using comparison operator
     * 
     * @param theElement the element to be found
     * @return the index of the found element, return -1 when not found
     */
    int indexOf(const T &theElement) const override;

    /**
     * @brief  Erase the index-th element
     */
    void erase(int index) override;

    /**
     * @brief all the elements following element[index] including element[index] right shift one position, element[index]=new element
     */
    void insert(int index, const T &theElement) override;

    /**
     * @brief Print the linearlist to output stream
     * 
     * @param out The output stream object
     */
    void output(std::ostream &out) const override;

    //Array Method
    int capacity() const { return m_capacity; }

    /*迭代器*/
    class Iterator
    {
        T *m_position;
    public:
        /*5个typedef/using 使之成为双向迭代器*/
        using iterator_category=std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer=T*;
        using reference=T&;

        //构造函数
        Iterator(T* position = nullptr):m_position(position){}
        
        //解除引用运算符
        auto &operator*() const { return *m_position; }
        
        //箭头运算符
        auto* operator->() const { return m_position;}

        //迭代器向前
        auto& operator++() {++m_position; return *this;}
        auto operator++(int) { auto old = *this;  ++m_position; return old;}

        //迭代器向后
        auto& operator--(){--m_position; return *this;}
        auto operator--(int) {auto old=*this; --m_position; return old;}

        //比较运算符
        auto operator!=(const Iterator right) const { return m_position != right.m_position; }
        auto operator==(const Iterator right) const { return m_position == right.m_position; }
    };

    /**
     * @brief 返回指向数组第一个元素的迭代器
     */
    auto begin() { return Iterator{elements}; }

    /**
     * @brief 返回指向数组超尾元素的迭代器
     */
    auto end() { return Iterator{elements + m_size}; }
};

template <typename T>
void ArrayList<T>::indexCheck(int index) const
{
    if (index < 0 || index >= m_size) //0<=index<=size-1
        throw std::out_of_range{std::string{"Accessing "} + std::to_string(index)};
}

template <typename T>
void ArrayList<T>::changeLength(int newLength)
{
    if(newLength < 0)
        throw std::bad_array_new_length{};
    auto temp=new T[newLength];
    std::copy(elements, elements+std::min(m_size, newLength), temp);
    delete[] elements;
    elements=temp;
    m_capacity=newLength;
}

template <typename T>
ArrayList<T>::ArrayList(int initialCapacity) : ArrayList(0, initialCapacity)
{
}

template <typename T>
ArrayList<T>::ArrayList(int increaseWhenFull, int initialCapacity):m_increaseSize(increaseWhenFull), m_size(0), m_capacity(initialCapacity)
{
    if(initialCapacity < 0)
        throw std::bad_array_new_length{};
    elements = new T[initialCapacity];
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &arrayToCopy)
{
    elements = new T[arrayToCopy.capacity];
    std::copy(arrayToCopy.elements, &(arrayToCopy.elements[capacity]), elements);
    capacity = arrayToCopy.capacity;
    size = arrayToCopy.size;
}


template <typename T>
T &ArrayList<T>::get(int index) const
{
    indexCheck(index);
    return elements[index];
}

template <typename T>
int ArrayList<T>::indexOf(const T &theElement) const
{
    if(auto iter = std::find(elements, elements+m_size, theElement); iter!=elements+m_size)
        return std::distance(elements, iter);
    else
        return -1;
}

template <typename T>
void ArrayList<T>::erase(int index)
{
    indexCheck(index);
    std::copy(&elements[index + 1], &elements[m_size], &elements[index]);
    --m_size;
}

template <typename T>
void ArrayList<T>::insert(int index, const T &theElement)
{
    if (index < 0 || index > m_size)
    {
        throw std::out_of_range{std::string{"Inserting at "}+std::to_string(index)};
    }
    else
    {
        if (m_size != m_capacity)
        {
            //空间未满，把插入位置以及之后的元素向后移动一个位置
            std::copy_backward(&elements[index], &elements[m_size], &elements[m_size + 1]);
            elements[index] = theElement;
            ++m_size;
        }
        else
        {
            //空间已满，将数组长度加倍
            changeLength(m_capacity*2);
            insert(index, theElement);
        }
    }
}

template <typename T>
void ArrayList<T>::output(std::ostream &out) const
{
    std::copy(elements, &elements[m_size], std::ostream_iterator<T>(std::cout, " "));
}