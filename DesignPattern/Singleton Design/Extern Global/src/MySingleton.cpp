#include "../include/MySingleton.h"
#include <cstdio>
#include <utility>
#include <random>
#include <chrono>
#include <iostream>
#include <new>

static int nifty_counter;
static My_Singleton* buffer;
My_Singleton& singleton_obj = *buffer;


My_Singleton::My_Singleton():id(1)
{
	std::cout << "My singleton obj is initialized, id= " << id << '\n';
}

My_Singleton::~My_Singleton()
{
	puts("My singleton obj is destoried\n");
}

void My_Singleton::use()
{
	printf_s("My singleton obj is used %d time\n", ++use_count);
}


SingletonInitializer::SingletonInitializer()
{
	if (nifty_counter++ == 0)
	{
		buffer = new My_Singleton;
	}
}

SingletonInitializer::~SingletonInitializer()
{
	if (--nifty_counter == 0)
		singleton_obj.~My_Singleton();
}