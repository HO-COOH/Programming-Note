#pragma once

/**
 * @brief The abstract class of LinearList
 * 
 * @tparam T Type of the elements
 */
template<typename T>
class LinearList
{
public:
    /**
     * @brief Destroy the Linear List object
     * 
     */
    virtual ~LinearList() {}
    
    /**
     * @brief Return whether the linear list is empty
     */
    virtual bool empty() const=0;
    
    /**
     * @brief Return the number of elements in the linear list
     */
    virtual int size() const = 0;
    
    /**
     * @brief Get the element at i-th index
     * 
     * @param index Index of the element
     * @return T& A reference to the elements
     */
    virtual T& get(int index) const=0;
    
    /**
     * @brief Get the index of an element first appeared in the linear list, using comparison operator
     * 
     * @param theElement the element to be found
     * @return the index of the found element, return -1 when not found
     */
    virtual int indexOf(const T& theElement) const=0;

    /**
     * @brief  Erase the index-th element
     */
    virtual void erase(int index)=0;
    
    /**
     * @brief all the elements following element[index] including element[index] right shift one position, element[index]=new element
     */
    virtual void insert(int index, const T& theElement)=0;
    
    /**
     * @brief Print the linearlist to output stream
     * 
     * @param out The output stream object
     */
    virtual void output(std::ostream& out) const=0;
};