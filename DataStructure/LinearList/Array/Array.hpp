#pragma once
#include <iterator>
#include <iostream>
#include <algorithm>
#include <stdexcept>

/*Abstract class of LinearList*/
#include "../LinearList.hpp"
#include <optional>
#include <new>
#include <memory>
#include <iterator>

/*Definition of Array*/
template <typename T>
class ArrayList : public LinearList<T>
{
protected:
    T *elements;                      //data
    int m_capacity;                   //capacity of the Array
    int m_listSize;                       //number of elements in the Array
    std::optional<int> m_increaseSize;         //练习4新增
    
    /**
     * @brief 检查下标是否越界，范围必须是(0, m_listSize]之间
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
    bool empty() const override { return m_listSize == 0; }

    /**
     * @brief Return the number of elements in the linear list
     */
    int size() const override { return m_listSize; }

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
    auto begin() const { return Iterator{elements}; }

    /**
     * @brief 返回指向数组超尾元素的迭代器
     */
    auto end() const { return Iterator{elements + m_listSize}; }

    /**
     * @brief 练习5，编写一个方法，它使数组的长度等于max{m_listSize, 1}
     * 
     * @details 复杂度：O(max(listSize, 1))
     */
    void trimToSize();

    /**
     * @brief 练习6，使线性表的大小等于指定大小，若线性表的大小小于指定的大小，则不增加元素，若线性表的大小大于指定的大小，则删除多余的元素
     * 
     * @details 复杂度：O(max(newSize-listSize, 0))
     */
    void setSize(int newSize);

    /**
     * @brief 练习7，重载操作符[]，使得表达式x[i]返回对线性表第i个元素的引用，若线性表没有第i个元素，则抛出异常
     * 
     * @details 其实就是get(i)，然而get()被声明为const成员函数，所以要重新定义一个
     */
    auto& operator[](int i)
    {
        indexCheck(i);
        return elements[i];
    }

    /**
     * @brief 练习8，重载操作符==，使得表达式x==y返回true当且仅当两个用数组描述的线性表x和y相等（即对所有的i，两个线性表的第i个元素相等）
     * 
     * @tparam U 右端数组的元素类型
     * @param rhs 右端数组
     * @details 注意这里应该定义成模板，使得即使两端数组的元素类型不同也可以比较
     */
    template<typename U>
    bool operator==(ArrayList<U> const &rhs) const
    {
        if(m_listSize==rhs.size()) //optimize a little bit
        {
            return std::equal(begin(), end(), rhs.begin());
        }
        else
            return false;
    }

    /**
     * @brief 练习9，重载操作符!=，使得表达式x!=y返回true，当且仅当两个用数组描述的线性表x和y不等
     * 
     * @tparam U 右端数组的元素类型
     * @param rhs 右端数组
     */
    template<typename U>
    bool operator!=(ArrayList<U> const &rhs) const
    {
        return !((*this) == rhs);
    }

    /**
     * @brief 练习10，重载操作符<，使得表达式x<y返回true，当且仅当用数组描述的线性表x按字典顺序小于用数组描述的线性表y
     * 
     * @tparam U 右端数组的元素类型
     * @param rhs 右端数组
     */
    template<typename U>
    bool operator<(ArrayList<U> const &rhs) const
    {
        if (auto [iter1, iter2] = std::mismatch(begin(), end(), rhs.begin()); iter1!=end() && iter2!=rhs.end())
            return *iter1 < *iter2;
        else
            return false;
    }

    /**
     * @brief 练习11，把元素theElement插到线性表的右端，不要利用insert方法
     * 
     * @param theElement 要插入的元素
     * @details 一次插入的时间显然是常数时间，注意应该定义两个重载，一个使用复制构造，一个使用移动构造
     * 我们来看看GCC 10.2中的std::vector::push_back()的实现：
     * 
     * //以下是vector类的定义
        
        namespace __gnu_cxx
        {
            template<typename _Alloc, typename = typename _Alloc::value_type>
            struct __alloc_traits : std::allocator_traits<_Alloc>
            {
                typedef std::allocator_traits<_Alloc>           _Base_type;
                typedef typename _Base_type::pointer            pointer;
                //...

                template<typename _Tp>
                struct rebind
                {
                    typedef typename _Base_type::template rebind_alloc<_Tp> other;
                };
            };
        }

        template<typename _Tp, typename _Alloc>
        struct _Vector_base
        {
            typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template rebind<_Tp>::other _Tp_alloc_type;
            typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer             pointer;

            struct _Vector_impl_data
            {
                pointer _M_start;
                pointer _M_finish;
                pointer _M_end_of_storage;
                //...
            };

            struct _Vector_impl : public _Tp_alloc_type, public _Vector_impl_data
            {
                //...
            };

            _Vector_impl _M_impl;

            pointer _M_allocate(size_t __n)
            {
                typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
	            return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();  //当__n==0时，返回空指针
            }
        };

        template<typename _Tp, typename _Alloc = std::allocator<_Tp>>
        class vector : protected _Vector_base<_Tp, _Alloc>
        {
            typedef _Vector_base<_Tp, _Alloc>		        	_Base;
            typedef typename _Base::_Tp_alloc_type	        	_Tp_alloc_type;
            typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Alloc_traits;
            //...


        };

        //push_back函数的定义
        void push_back(const value_type& __x)
        {
            if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)         //如果空间没有满
            {
                _GLIBCXX_ASAN_ANNOTATE_GROW(1);      //似乎是address sanitizer相关的宏，与实际程序无关：https://gcc.gnu.org/legacy-ml/gcc-patches/2017-07/msg01314.html
                _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
                ++this->_M_impl._M_finish;          //将数组末尾指针向前移动
                _GLIBCXX_ASAN_ANNOTATE_GREW(1);     //同上
            }
            else
                _M_realloc_insert(end(), __x);
        }

        void push_back(value_type&& __x)
        { 
            emplace_back(std::move(__x));   //在右值情况下，相当于直接使用emplace_back
        }

        typename vector<_Tp, _Alloc>::reference vector<_Tp, _Alloc>::emplace_back(_Args&&... __args) //C++17后该函数返回一个构造好的元素的引用
        {
            if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
            {
                _GLIBCXX_ASAN_ANNOTATE_GROW(1);
                _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, std::forward<_Args>(__args)...);
                ++this->_M_impl._M_finish;
                _GLIBCXX_ASAN_ANNOTATE_GREW(1);
            }
            else
                _M_realloc_insert(end(), std::forward<_Args>(__args)...);
            return back();
        }

        //push_back和emplace_back用到了_Alloc_traits::construct()和_M_realloc_insert()
        size_type _M_check_len(size_type __n, const char* __s) const
        {
            if (max_size() - size() < __n)
                __throw_length_error(__N(__s)); //如果剩余空间不够，抛出异常

            const size_type __len = size() + std::max(size(), __n);             //在空间足够的情况下，新长度要么加倍，要么增加n，选两个中大者
            return (__len < size() || __len > max_size()) ? max_size() : __len; //空间足够时，直接返回新长度，否则由于新长度比max_size()大，即空间不够，则只能增加到max_size()，
        }

        static constexpr bool _S_nothrow_relocate(true_type)
        {
            return noexcept(...);
        }

        static constexpr bool _S_use_relocate()
        {
            return _S_nothrow_relocate(__is_move_insertable<_Tp_alloc_type>{});
        }
        
        //在<stl_uninitialized.h>中有
        template<typename _InputIterator, typename _ForwardIterator, typename _Allocator>
        inline _ForwardIterator __relocate_a(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _Allocator& __alloc) noexcept(...)
        {
            return __relocate_a_1(std::__niter_base(__first), std::__niter_base(__last), std::__niter_base(__result), __alloc);
        }

        static pointer _S_do_relocate(pointer __first, pointer __last, pointer __result, _Tp_alloc_type& __alloc, true_type) noexcept
        {
            return std::__relocate_a(__first, __last, __result, __alloc);
        }

        template<typeame _Tp, typename _Alloc>
        template<typename..._Args>
        void vector<_Tp, _Alloc>::_M_realloc_insert(iterator __position, _Args&&... __args)
        {
            const size_type __len = _M_check_len(size_type(1), "vector::_M_realloc_insert");
            pointer __old_start = this->_M_impl._M_start;
            pointer __old_finish = this->_M_impl._M_finish;
            
            const size_type __elems_before = __position - begin();  //在插入位置之前的元素个数
            
            pointer __new_start(this->_M_allocate(__len));
            pointer __new_finish(__new_start);

            try{
                _Alloc_traits::construct(this->_M_impl, __new_start + __elems_before, std::forward<_Args>(__args)...);  //在新内存的正确位置构造元素新元素
                __new_finish = pointer();   //新的超尾指针赋值为空指针
                if constexpr(_S_use_relocate())
                {
                    __new_finish = _S_relocate(__old_start, __position.base(), __new_start, _M_get_Tp_allocator()); //使用relocate将插入位置之前的原来的元素移动到新内存，即[old_start, position) -> [new_start, ...)
                    ++__new_finish;
                    __new_finish = _S_relocate(__position.base(), __old_finish, __new_finish, _M_get_Tp_allocator());//[position, old_finish) -> [new_finish, ...)
                }
                else
                {
                    __new_finish = std::__uninitialized_move_if_noexcept_a(__old_start, __position.base(), __new_start, _M_get_Tp_allocator());
                    ++__new_finish;
                    __new_finish = std::uninitialized_move_if_noexcept_a(__position.base(), __old_finish, __new_finish, _M_get_Tp_allocator());
                }
            }
            catch(...){
                //如果有错误发生，则先析构对象，再释放新内存，最后重新抛出，注意此时旧内存完全没动
                if(!__new_finish)
                    _Alloc_traits::destory(this->_M_impl, __new_start + __elems_before);
                else
                    std::_Destory(__new_start, __new_finish, _M_get_Tp_allocator());
                _M_deallocate(__new_start, __len);
                throw;
            }
            //如果没有错误发生，释放旧内存，再更新指针
            if constexpr(!_S_use_relocate())
                std::_Destory(__old_start, __old_finish, _M_get_Tp_allocator());
            _M_deallocate(__old_start, this->_M_impl._M_end_of_storage - __old_start);
            this->_M_impl._M_start = __new_start;
            this->_M_impl._M_finish = __new_finish;
            this->_M_impl._M_end_of_storage = __new_start + __len;
        }
     */
private:
    template<typename... Args>
    static void construct(T const* const position, Args&&... args)
    {
        new ((void *)position) T(std::forward<Args>(args)...);
    }
public:
    void push_back(T const& theElement)
    {
        if (m_listSize != m_capacity)
        {
            //elements[m_listSize] = theElement;
            construct(elements + m_listSize, theElement);
        }
        else
        {
            //空间已满，将数组长度加倍
            changeLength(m_increaseSize.has_value()? *m_increaseSize+m_capacity : m_capacity*2);
            //elements[m_listSize++] = theElement;
            construct(elements + m_listSize, theElement);
        }
        ++m_listSize;
    }
    void push_back(T&& theElement)
    {
        if (m_listSize != m_capacity)
        {
            elements[m_listSize] = std::move(theElement);
            ++m_listSize;
        }
        else
        {
            //空间已满，将数组长度加倍
            changeLength(m_increaseSize.has_value()? *m_increaseSize+m_capacity : m_capacity*2);
            elements[m_listSize++] = std::move(theElement);
        }
    }

    /**
     * @brief 练习12：把线性表右端的元素删除，不要利用erase方法
     * 
     * @details 时间复杂度O(1)
     */
    void pop_back()
    {
        --m_listSize;
    }

    /**
     * @brief 练习13：交换线性表的元素*this和theList，由于这里没有说是用数组描述的线性表，所以用多态的方法
     * 
     * @param theList 要交换的右端线性表
     */
    void swap(LinearList<T>& theList)
    {
        std::swap_ranges(begin(), end(), &theList.get(0));
    }

    /**
     * @brief 练习14：把数组容量改变为当前容量和theCapacity的较大者
     * 
     * @param theCapacity 新的容量大小
     */
    void reserve(int theCapacity)
    {
        changeLength(std::max(theCapacity, m_capacity));
    }

    /**
     * @brief 练习15：用元素theElement替换索引为theIndex的元素，若索引theIndex超出范围，则抛出异常
     * 
     * @param theIndex 
     * @param theElement 
     * @returns 返回原来索引为theIndex的元素
     */
    T set(int theIndex, T const& theElement)
    {
        indexCheck(theIndex);
        return std::exchange(elements[theIndex], theElement);
    }

    /**
     * @brief 练习16：使线性表为空
     */
    void clear()
    {
        m_listSize = 0;
    }

    /**
     * @brief 练习17：删除指定索引范围[from, to]内的所有元素
     * 
     * @param from 
     * @param to 
     */
    void removeRange(int from, int to)
    {
        if(to < from)
            throw std::range_error{"to < from"};
        indexCheck(from);
        indexCheck(to);
        std::move_backward(begin() + to + 1, end(), begin() + from);
        m_listSize -= (to - from + 1);
    }

    /**
     * @brief 练习18：返回指定元素最后出现时的索引
     * 
     * @param theElement 
     * @return int 
     */
    int lastIndexOf(T const& theElement)
    {
        return std::distance(begin(), std::find(std::make_reverse_iterator(end()--), std::make_reverse_iterator(begin()), theElement));
    }

    /**
     * @brief 练习22：原地颠倒
     */
    void reverse()
    {
        std::reverse(begin(), end());
    }
};

template <typename T>
void ArrayList<T>::indexCheck(int index) const
{
    if (index < 0 || index >= m_listSize) //0<=index<=size-1
        throw std::out_of_range{std::string{"Accessing "} + std::to_string(index)};
}

template <typename T>
void ArrayList<T>::changeLength(int newLength)
{
    if(newLength < 0)
        throw std::bad_array_new_length{};
    auto temp=new T[newLength];
    m_listSize = std::min(m_listSize, newLength);
    std::uninitialized_move_n(elements, m_listSize, temp);
    delete[] elements;
    elements=temp;
    m_capacity=newLength;
}

template <typename T>
ArrayList<T>::ArrayList(int initialCapacity) : m_capacity(initialCapacity), m_listSize(0)
{
    if(initialCapacity < 0)
        throw std::bad_array_new_length{};
    elements = new T[initialCapacity];
}

template <typename T>
ArrayList<T>::ArrayList(int increaseWhenFull, int initialCapacity):  m_capacity(initialCapacity), m_listSize(0), m_increaseSize(increaseWhenFull)
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
    if(auto iter = std::find(elements, elements+m_listSize, theElement); iter!=elements+m_listSize)
        return std::distance(elements, iter);
    else
        return -1;
}

template <typename T>
void ArrayList<T>::erase(int index)
{
    indexCheck(index);
    std::copy(&elements[index + 1], &elements[m_listSize], &elements[index]);
    --m_listSize;
}

template <typename T>
void ArrayList<T>::insert(int index, const T &theElement)
{
    if (index < 0 || index > m_listSize)
    {
        throw std::out_of_range{std::string{"Inserting at "}+std::to_string(index)};
    }
    else
    {
        if (m_listSize != m_capacity)
        {
            //空间未满，把插入位置以及之后的元素向后移动一个位置
            std::copy_backward(&elements[index], &elements[m_listSize], &elements[m_listSize + 1]);
            elements[index] = theElement;
            ++m_listSize;
        }
        else
        {
            //空间已满，将数组长度加倍
            changeLength(m_increaseSize.has_value()? *m_increaseSize+m_capacity : m_capacity*2);
            insert(index, theElement);
        }
    }
}

template <typename T>
void ArrayList<T>::output(std::ostream &out) const
{
    std::copy(elements, &elements[m_listSize], std::ostream_iterator<T>(std::cout, " "));
}

template<typename T>
void ArrayList<T>::trimToSize()
{
    changeLength(std::max(m_listSize, 1));
}

template<typename T>
void ArrayList<T>::setSize(int newSize)
{
    if(m_listSize > newSize)
        changeLength(newSize);
}