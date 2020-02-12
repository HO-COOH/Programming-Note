#pragma once
#include <iostream>
class My_Singleton
{
	My_Singleton(My_Singleton&&) =delete;
	My_Singleton& operator=(My_Singleton&&) = delete;
	int use_count = 0;
	std::ios_base::Init initalizer;
public:	
	My_Singleton();
	~My_Singleton();
	My_Singleton& operator=(const My_Singleton&) = default;
	void use();
	int id;
};

extern My_Singleton& singleton_obj;

static struct SingletonInitializer
{
	SingletonInitializer();
	~SingletonInitializer();
} initializer;
