#include <iostream>
#include <iterator>

/*Abstract class of LinearList*/
#include "../LinearList.hpp"

/*Definition of Array*/
template<typename T>
class Array: public LinearList<T>
{
private:
    T* elements;        //data
    int _capacity;       //capacity of the Array
    int listSize;       //number of elements in the Array
    bool IndexCheck(int index) const;
public:
    Array(int initialCapacity=10);  //Constructor with an initialCapacity
    Array(const Array<T>&);         //Copy constructor
    
    ~Array(){delete[] elements;}    //Destructor

    //Linear List Methods
    bool empty() const {return listSize==0;}
    int size() const {return listSize;}
    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void erase(int index);
    void insert(int index, const T& theElement);
    void output(std::ostream& out) const;

    //Array Method
    int capacity() const {return _capacity;}
};

template<typename T>
Array<T>::Array(int initialCapacity):_capacity(initialCapacity), listSize(0)
{
    elements=new T[initialCapacity];
}

template<typename T>
Array<T>::Array(const Array<T>& arrayToCopy)
{
    elements=new T[arrayToCopy._capacity];
    std::copy(arrayToCopy.elements, &(arrayToCopy.elements[_capacity]),elements);
    _capacity=arrayToCopy._capacity;
    listSize=arrayToCopy.listSize;
}

template<typename T>
bool Array<T>::IndexCheck(int index) const
{
    if(index<0||index>=listSize)    //0<=index<=listSize-1
    {
        std::cout<<"Invalid index" <<index<<std::endl;
        return false;
    }
    return true;
}

template<typename T>
T& Array<T>::get(int index) const
{
    if(IndexCheck(index))
    {
        return elements[index];
    }
    abort();
}

template<typename T>
int Array<T>::indexOf(const T& theElement) const
{
    for(int i=0; i<_capacity; ++i)
    {
        if(theElement==elements[i])
            return i;
    }
    std::cout<<"The element "<<theElement<<"is not found in the list!\n";
    return -1;
}

template<typename T>
void Array<T>::erase(int index)
{
    if(IndexCheck(index))
        std::copy(&elements[index+1],&elements[listSize],&elements[index]);
    --listSize;
}

template<typename T>
void Array<T>::insert(int index, const T& theElement)
{
    if(index<0||index>listSize)
    {
        std::cout<<"Insert at index"<<index<<"error\n";
        return;
    }
    else
    {
        if(listSize!=_capacity)
        {
            std::copy_backward(&elements[index],&elements[listSize],&elements[++listSize]);
            elements[index]=theElement;
        }
        else
            std::cout<<"The Array is full!\n";
    }
}

template<typename T>
void Array<T>::output(std::ostream& out) const
{
    std::copy(elements,&elements[listSize],std::ostream_iterator<T,char>(std::cout," "));
}