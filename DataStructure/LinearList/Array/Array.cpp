#include "Array.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;

void Random_Insert_Test()
{
    Array<int> a;
    for(int i=0;i<10;++i)
    {
        a.insert(i,rand());
    }
    a.output(cout);
}

void Manual_Insert_And_Find_Test()
{
    Array<int>a(5);
    a.insert(0,2);
    a.insert(1,3);
    a.insert(2,10);
    a.insert(3,0);
    a.insert(4,20);
    //a.insert(5,11);
    a.output(cout); //should be: 2 3 10 0 20
    a.erase(2);     //should be: 2 3 0 20
    a.output(cout);
    a.get(3);       //should be 20
    cout<<endl<<"The index of element 20 is "<<a.indexOf(20)<<endl;  //should be 3
    cout<<"The size of array is "<<a.size()<<endl;  //should be 4
    cout<<"The capacity of array is "<<a.capacity()<<endl;  //should be 5
}

int main()
{
    srand(unsigned(time(NULL)));
    /*Tests*/
    Random_Insert_Test();
    cout<<endl;
    Manual_Insert_And_Find_Test();

}