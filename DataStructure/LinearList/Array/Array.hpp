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
    int m_capacity;                     //capacity of the Array
    int m_size;                         //number of elements in the Array
    int const m_increaseSize;         //练习4新增
    void indexCheck(int index) const; //if index is invalid, throw std::out_of_range exception
    void changeLength(int newLength); //if newLength is invalid, throw std::bad_array_new_length
public:
    ArrayList(int initialCapacity = 10); //Constructor with an initialCapacity
    
    /**
     * @brief 允许构造时指定数组空间满时数组长度的增加量
     * @param increaseWhenFull 数组空间满时数组长度的增加量
     * @param initialCapacity 构造时预分配的内存大小
     */
    ArrayList(int increaseWhenFull, int initialCapacity);

    ArrayList(const ArrayList<T> &); //Copy constructor

    ~ArrayList() { delete[] elements; } //Destructor

    //Linear List Methods
    bool empty() const override { return m_size == 0; }
    int size() const override { return m_size; }
    T &get(int index) const override;
    int indexOf(const T &theElement) const override;
    void erase(int index) override;
    void insert(int index, const T &theElement) override;
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
        auto &operator*() const { return *m_position; }
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

    auto begin() { return Iterator{elements}; }
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