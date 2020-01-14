#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>

template<typename ELEMENT>
struct SkipNode
{
	ELEMENT element;
	std::vector<SkipNode<ELEMENT>*> next;
};

#ifdef TEST_BUILD
#define private public
#endif

template<typename ELEMENT>
class SkipList
{
private:
	const int maxLevel;
	const float probability;
	unsigned count = 0;
	int currentLevel = 0;
	SkipNode<ELEMENT>* head= new SkipNode<ELEMENT>{ ELEMENT(), {nullptr} };
	SkipNode<ELEMENT>* tail= new SkipNode<ELEMENT>{ ELEMENT(), {nullptr} };

	void deleteAll();
	int level();
	SkipNode<ELEMENT>* find(ELEMENT element) const;
	
public:
	SkipList(int maxLevel, float probability) :maxLevel(maxLevel), probability(probability) { head->next[0] = tail; }
	/*SkipList iterator*/
	template<typename _ELEMENT>
	class SkipListIter
	{
		SkipNode<_ELEMENT>* ptr;
	public:
		SkipListIter(SkipNode<_ELEMENT>* node):ptr(node) {}
		_ELEMENT& operator*() { return ptr->element; }
		SkipListIter& operator++() { ptr=ptr->next[0]; return *this; }
		bool operator!=(const SkipListIter& rhs) const { return ptr != rhs.ptr; }
	};

	SkipListIter<ELEMENT> begin() const { return SkipListIter<ELEMENT>(head); }
	//SkipListIter<ELEMENT> end() const {}
	SkipList(const SkipList& list) = delete;
	SkipList(const SkipList<ELEMENT>&& list) noexcept;
	SkipList& operator=(const SkipList& list) = delete;
	SkipList& operator=(SkipList&& list) noexcept;
	~SkipList() = default;
	void insert(ELEMENT element);
	void erase(ELEMENT element);

	void print_all() const;
};

template<typename ELEMENT>
void SkipList<ELEMENT>::deleteAll()
{
	auto current = head;
	auto next = current->next.empty() ? nullptr : current->next[0];
	while(current!=nullptr)
	{
		delete current;
		if (next == nullptr)
			break;
		current = next;
		next = current->next.empty() ? nullptr : current->next[0];
	}
	head = nullptr;
}

template<typename ELEMENT>
int SkipList<ELEMENT>::level()
{
	static std::mt19937 rd(std::chrono::steady_clock::now().time_since_epoch().count());
	static std::uniform_real_distribution<float> rd_num(0,1);
	int level = 0;
	while(rd_num(rd) <= probability && level <= currentLevel)
		++level;
	if(level>currentLevel)
		++currentLevel;
	return level;
}

template<typename ELEMENT>
SkipNode<ELEMENT>* SkipList<ELEMENT>::find(ELEMENT element) const
{
	if (count==0 || element<head->next[0]->element)
		return nullptr;
	auto last = head;
	for(auto i=currentLevel; i>=0; --i)
	{
		while (last->next[i]->element < element && last->next[i]!=tail)
			last = last->next[i];
	}
	return (last->next[0]->element == element? (last->next[0]) : nullptr);
}

template <typename ELEMENT>
SkipList<ELEMENT>::SkipList(const SkipList<ELEMENT>&& list) noexcept :maxLevel(list.maxLevel), probability(list.probability)
{
	deleteAll();
	head = list.head;
	list.head = nullptr;
}

template<typename ELEMENT>
SkipList<ELEMENT>& SkipList<ELEMENT>::operator=(SkipList<ELEMENT>&& list) noexcept
{
	deleteAll();
	head = list.head;
	list.head = nullptr;
	return *this;
}

template<typename ELEMENT>
void SkipList<ELEMENT>::insert(ELEMENT element)
{
	std::cout << "Insert: " << element << '\n';
	if (auto node = find(element); node != nullptr)	//there is existing node, update 
	{
		node->element = element;
		return;
	}
	
	//no existing, insert new node
	auto newNode = new SkipNode<ELEMENT>{ element, {} };
	newNode->next.resize(level()+1);

	
	for (auto level = static_cast<int>(newNode->next.size()-1); level >= 0; --level)
	{
		if(level>head->next.size()-1)
		{
			head->next.push_back(newNode);
			newNode->next.back() = tail;
		}
		else
		{
			auto last = head;
			while (last->next[level] != nullptr && last->next[level]->element < element && last->next[level] != tail)
				last = last->next[level];
			newNode->next[level] = last->next[level];
			last->next[level] = newNode;
		}
	}
	++count;
}

template<typename ELEMENT>
void SkipList<ELEMENT>::erase(ELEMENT element)
{
	if(auto node=find(element); node!=nullptr)
	{
		std::cout << "Erase " << element << '\n';
		for(auto i=static_cast<int>(node->next.size()-1); i>=0; --i)
		{
			//find the node pointing to this node at level i
			auto last = head;
			while (last->next[i]->element < element)
				last = last->next[i];
			if (node->next[i] == tail)
				last->next.pop_back();
			else
				last->next[i] = node->next[i];
		}
		delete node;
		--count;
	}
	else
		std::cout << "The element " << element << " not found!\n";
}

template <typename ELEMENT>
void SkipList<ELEMENT>::print_all() const
{
	if (count==0)
		std::cout << "Empty skip list!\n";
	else
	{
		std::cout << "head(" << head->next.size()-1 << ")-> ";
		auto current = head->next[0];
		while (current != nullptr && current!=tail)
		{
			std::cout << current->element <<'('<<current->next.size()-1<< ")-> ";
			current = current->next[0];
		}
		std::cout << "tail\n";
	}
	
}
	