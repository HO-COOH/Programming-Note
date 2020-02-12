#include "../include/UseSingleton.h"
#include <cstdio>

void UseSingleton()
{
	puts("Use MySingleton in UseSingleton.cpp");
	std::cout << "My singleton in UseSingleton.cpp : " << &singleton_obj << '\n';
	singleton_obj.use();
}