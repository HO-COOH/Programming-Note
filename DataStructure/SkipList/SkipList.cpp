#define TEST_BUILD			//define this to make private class member public
#include "SkipList.h"
#include <gtest/gtest.h>

using namespace std;


TEST(EmptySkipList, EmptySkipListTest)
{
	SkipList<int> list{ 5,0.5f };
	EXPECT_EQ(list.count, 0);
	EXPECT_EQ(list.maxLevel, 5);
	EXPECT_EQ(list.currentLevel, 0);
	EXPECT_EQ(list.head->next.size(), 1);
	list.deleteAll();
	EXPECT_EQ(list.head, nullptr);
	EXPECT_EQ(list.count, 0);
}

TEST(InsertInt, Insert)
{
	SkipList<int> list{ 5, 0.5f };
	list.print_all();
	list.insert(80);
	list.insert(40);
	list.insert(30);
	list.insert(24);
	list.insert(20);
	list.insert(3);
	list.insert(11);
	list.insert(9);
	list.insert(7);

	list.print_all();

	auto list_iter = list.begin();
	++list_iter;
	EXPECT_EQ(*list_iter, 3);
	++list_iter;
	EXPECT_EQ(*list_iter, 7);
	++list_iter;
	EXPECT_EQ(*list_iter, 9);
	++list_iter;
	EXPECT_EQ(*list_iter, 11);
	++list_iter;
	EXPECT_EQ(*list_iter, 20);
	++list_iter;
	EXPECT_EQ(*list_iter, 24);
	++list_iter;
	EXPECT_EQ(*list_iter, 30);
	++list_iter;
	EXPECT_EQ(*list_iter, 40);
	++list_iter;
	EXPECT_EQ(*list_iter, 80);

	EXPECT_EQ(list.count, 9);
}

TEST(InsertInt, InsertAndErase)
{
	SkipList<int> list{ 5, 0.5f };
	list.print_all();
	list.insert(80);
	list.insert(40);
	list.insert(30);
	list.insert(24);
	list.insert(20);
	list.insert(3);
	list.insert(11);
	list.insert(9);
	list.insert(7);

	list.print_all();
	
	auto count = list.count;
	list.erase(3);
	
	auto get_first_node = [](const auto& list) {auto list_iter = list.begin(); ++list_iter; return list_iter; };//a lambda to get iterator pointing to the first node after head
	EXPECT_EQ(*get_first_node(list), 7);
	EXPECT_EQ(list.count, count - 1);

	list.erase(7);
	EXPECT_EQ(*get_first_node(list), 9);
	
	list.erase(1);	//1 not exist
	EXPECT_EQ(*(get_first_node(list)), 9);
	EXPECT_EQ(list.count, count - 2);

	list.erase(11);
	list.erase(80);
	list.erase(24);
	list.erase(20);
	list.erase(9);
	list.erase(40);
	list.erase(30);

	EXPECT_EQ(list.count, 0);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
