#pragma once
#include <utility>
template<typename Key, typename Value>
class Dictionary
{
public:
    virtual ~Dictionary() {}
    virtual bool empty() const = 0;                                     //return true if the dictionary is empty
    virtual int size() const = 0;                                       //return the number of pairs in the dictionary
    virtual std::pair<const Key, Value>& find(const Key& key) = 0;      //return a pointer of the pair of Key:key
    virtual void erase(const Key& key) = 0;                             //delete the pair of Key:key
    virtual void insert(const std::pair<const Key, Value>& pair) = 0;   //insert a new pair of <Key, Value>, if a key already exists, new value:Value is replaced, else insert the new key and value
};

