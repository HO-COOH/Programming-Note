/*definition of Node*/
#include "../LinearList.hpp"

template<typename T>
struct Node
{
    /*data members*/
    T element;
    Node<T> *next;

    /*Methods*/
    Node(){}
    Node(const T& element)
    {
        this->element=element;
    }
    Node(const T& element, Node<T>* next)
    {
        this->element=element;
        this->next=next;
    }
};

template<typename T>
class SinglyLinkedList :public LinearList<T>
{
private:
    Node<T>* head=nullptr;
    int listSize=0;
public:
    SinglyLinkedList() {}
    SinglyLinkedList(const SinglyLinkedList<T>&);
    ~SinglyLinkedList();

    /*Linear List Methods*/
    bool empty() const
    {
        return listSize==0;
    }
    int size() const
    {
        return listSize;
    }
    T& get(int index) const;
    int indexOf(const T& element) const;
    void erase(int index);
    void insert(int index, const T& element);
    void output(std::ostream& out) const;

    /*SinglyLinked List Methods*/
    void clear();
    void push_back(const T& element);
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& listToCopy)
{
    head=listToCopy.head;
    listSize=listToCopy.listSize;
    Node<T>* currentNode=listToCopy.head->next;
    while(currentNode!=nullptr)
    {
        Node<T>* thisNode=new Node<T>(currentNode->element);
        currentNode=currentNode->next;
    }
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    Node<T>* currentNode;
    while(head!=nullptr)
    {
        currentNode=head->next;
        delete head;
        head=currentNode;
    }
}



template<typename T>
T& SinglyLinkedList<T>::get(int index) const
{
    int current=0;
    Node<T>* currentNode=head;
    while(current!=index&&currentNode!=nullptr)
    {
        currentNode=currentNode->next;
        ++current;
    }
    if(currentNode==nullptr)
    {
        std::cout<<"The index "<<index<<" is not found in Linked List!\n";
        return head->element;
    }
    return currentNode->element;
}

template<typename T>
int SinglyLinkedList<T>::indexOf(const T& element) const
{
    int current=0;
    Node<T>* currentNode=head;
    while(currentNode!=nullptr&&currentNode->element!=element)
    {
        currentNode=currentNode->next;
        ++current;
    }
    if(currentNode==nullptr)
    {
        std::cout<<"The element "<<element<<"is not found in Linked List!\n";
        return -1;
    }
    return current;
}

template<typename T>
void SinglyLinkedList<T>::erase(int index)
{
    if(index==0)
    {
        Node<T>* currentNode=head->next;
        delete head;
        head=currentNode;
        --listSize;
    }
    else
    {
        int current=0;
        Node<T>* front=head;
        while(front->next!=nullptr&&current!=index-1)
        {
            front=front->next;
            ++current;
        }
        if(front->next==nullptr)
        {
            std::cout<<"The index "<<index<<" to erase is invalid!\n";
        }
        else
        {
            Node<T>* current=front->next;
            front->next=current->next;
            delete current;
            --listSize;
        }
    }
}

template<typename T>
void SinglyLinkedList<T>::insert(int index, const T& element)
{
    if(index==0)
    {
        Node<T>* newHead=new Node<T>;
        newHead->element=element;
        newHead->next=head;
        head=newHead;
        ++listSize;
    }
    else
    {
        int current=0;
        Node<T>* front=head;
        while(front->next!=nullptr&&current!=index-1)
        {
            front=front->next;
            ++current;
        }
        if(current==index)
            std::cout<<"The index "<<index<<" to insert is invalid!\n";
        else
        {
            Node<T>* newNode=new Node<T>;
            newNode->element=element;
            newNode->next=front->next;
            front->next=newNode;
            ++listSize;
        }
    }
}

template<typename T>
void SinglyLinkedList<T>::output(std::ostream& out) const
{
    Node<T>* currentNode=head;
    int index=0;
    while(currentNode!=nullptr)
    {
        out<<"The "<<index<<" node: "<<currentNode->element<<std::endl;
        ++index;
        currentNode=currentNode->next;
    }
}

template<typename T>
void SinglyLinkedList<T>::clear()
{
    Node<T>* currentNode;
    while(head!=nullptr)
    {
        currentNode=head->next;
        delete head;
        head=currentNode;
    }
    listSize=0;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& element)
{
    Node<T>*currentNode=head;
    while(currentNode->next!=nullptr)
    {
        currentNode=currentNode->next;
    }
    currentNode->next=new Node<T>;
    (currentNode->next)->element=element;
    (currentNode->next)->next=nullptr;
    ++listSize;
}