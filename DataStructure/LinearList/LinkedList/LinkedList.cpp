#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.hpp"

using namespace std;

void Random_Insert_Test()
{
    cout<<"Random Insert Test:\n";

    srand(unsigned(time(NULL)));

    SinglyLinkedList<double> a;
    for(int i=0; i<10; ++i)
    {
        a.insert(i,static_cast<double>(rand())/10);
    }
    cout<<"The size of Linked List is "<<a.size()<<endl;

    for(int i=0;i<10;++i)
    {
        a.push_back(static_cast<double>(rand()%100));
    }
    a.output(cout);
    cout<<"Now the size of the list is "<<a.size()<<endl;
    a.erase(2);
    cout<<"Now the size of the list after erase is "<<a.size()<<endl;
    a.output(cout);
    a.clear();
    cout<<"Now the size of the list after clear is "<<a.size()<<endl;
    a.output(cout);
}

int main()
{
    Random_Insert_Test();
}