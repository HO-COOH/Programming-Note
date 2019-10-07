#include <memory>
#include <optional>
#include <iostream>
#include <cmath>

template<typename T>
class maxHeap
{
	std::unique_ptr<T[]> heap;
	size_t arrayLength;
	size_t heapSize = 0;
public:
	maxHeap(size_t _arrayLength);

	template<typename iter>
	static void my_make_heap(iter begin, iter end);

	std::optional<T> top() const;
	void push(const T& element);
	void pop();
	void print() const;
};

template<typename T>
maxHeap<T>::maxHeap(size_t _arrayLength) :arrayLength(_arrayLength), heap(std::make_unique<T[]>(_arrayLength + 1))
{}

template<typename T>
template<typename iter>
void maxHeap<T>::my_make_heap(iter begin, iter end)
{
    if(std::is_same<std::random_access_iterator_tag, typename std::iterator_traits<iter>::iterat)
}

template<typename T>
std::optional<T> maxHeap<T>::top() const
{
	if (heapSize > 0)
		return heap[1];
	else
	{
		return {};
	}
}

template<typename T>
void maxHeap<T>::push(const T& element)
{
	if (heapSize == arrayLength - 1) //double the length of the heap
	{
		arrayLength *= 2;
		T* ptr_temp = new T[arrayLength];
		std::copy(heap.get(), heap.get()+arrayLength, ptr_temp);
		heap.reset(ptr_temp);
	}
	size_t currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < element)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = element;
}

template<typename T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
		std::cout << "heap size=0\n";
	T lastElement = heap[heapSize--];
	size_t currentNode = 1, child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
			++child;
		if (lastElement >= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<typename T>
void maxHeap<T>::print() const
{
	size_t currentLevel = 0;
	size_t currentNode = 0;
	size_t count = 0;
	std::cout << "Heap size=" << heapSize << std::endl;
	std::cout << "Array Length=" << arrayLength << std::endl;
	while (currentNode++ != heapSize)
	{
		std::cout << heap[currentNode]<<" ";
		if (++count == (int)pow(2, currentLevel))
		{
			std::cout << std::endl;
			++currentLevel;
			count = 0;
		}
	}
}
