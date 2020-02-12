#include "../include/MySingleton.h"
#include "../include/UseSingleton.h"
#include <cstdio>

int main()
{
	int* pt = nullptr;
	int& a = *pt;
	pt = new int(3);
	std::cout<<"a=" << a<<'\n';
}