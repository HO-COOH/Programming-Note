#include "Array.hpp"
#include <gtest/gtest.h>
#include <random>
#include <unordered_map>

TEST(ArrayList, DefaultArrayList)
{
    ArrayList<int> arr;
    EXPECT_EQ(arr.capacity(), 10);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayList, EmptyArrayList)
{
    ArrayList<int> arr{0};
    EXPECT_EQ(arr.capacity(), 0);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayList, InsertFront)
{
    ArrayList<int> arr;
    arr.insert(0, 10);
    arr.insert(0, 11);
    arr.insert(0, 12);
    EXPECT_EQ(arr.get(0), 12);
    EXPECT_EQ(arr.get(1), 11);
    EXPECT_EQ(arr.get(2), 10);
}

TEST(ArrayList, InsertBack)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 11);
    EXPECT_EQ(arr.get(2), 12);
}

TEST(ArrayList, InsertNegative)
{
    ArrayList<int> arr;
    arr.insert(0, 10);
    EXPECT_ANY_THROW(arr.insert(-1, 11));
}

TEST(ArrayList, InsertWrong)
{
    ArrayList<int> arr;
    EXPECT_ANY_THROW(arr.insert(1, 1));
}

TEST(ArrayList, GetWrong)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    EXPECT_ANY_THROW(arr.get(3));
}

TEST(ArrayList, IncreaseSize)
{
    ArrayList<int> arr{5};
    EXPECT_EQ(arr.capacity(), 5);
    for (auto i = 0; i < 5; ++i)
    {
        arr.insert(arr.size(), i + 10);
        EXPECT_EQ(arr.capacity(), 5);
    }
    arr.insert(arr.size(), 20);
    EXPECT_EQ(arr.capacity(), 10);
}

TEST(ArrayList, FindElement)
{
    std::mt19937 eng{std::random_device{}()};
    constexpr int testSize = 50;
    ArrayList<int> arr{testSize};
    std::unordered_map<int, int> numbers;   //{element, indices}
    for (auto i = 0; i < testSize; ++i)
    {
        auto const number = eng();
        arr.insert(arr.size(), number);
        if (auto iter = numbers.find(number);  iter!= numbers.cend())
            iter->second = std::min(iter->second, i);
        else
            numbers[number] = i;
    }
    for(auto element:numbers)
    {
        auto const findResult = arr.indexOf(element.first);
        EXPECT_NE(findResult, -1);
        EXPECT_EQ(findResult, element.second);
    }
}

TEST(ArrayList, EraseFront)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    arr.erase(0);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), 11);
    EXPECT_EQ(arr.get(1), 12);
}

TEST(ArrayList, EraseBack)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    arr.erase(2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(ArrayList, EraseEmpty)
{
    ArrayList<int> arr;
    EXPECT_ANY_THROW(arr.erase(0));
}

TEST(ArrayList, EraseNegative)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    EXPECT_ANY_THROW(arr.erase(-1));
}

TEST(ArrayList, EraseWrong)
{
    ArrayList<int> arr;
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    EXPECT_ANY_THROW(arr.erase(arr.size()));
}

TEST(Practice4, SpecifyIncreasingSize)
{
    ArrayList<int> arr{2, 3};
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 3);
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr.capacity(), 3);
    arr.insert(arr.size(), 13);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.capacity(), 5);
}

TEST(Practice5, TrimToSize0)
{
    ArrayList<int> arr{3};
    arr.trimToSize();
    EXPECT_EQ(arr.capacity(), 1);
}

TEST(Practice5, TrimToSize1)
{
    ArrayList<int> arr{3};
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    arr.insert(arr.size(), 13);
    arr.trimToSize();
    EXPECT_EQ(arr.size(), arr.capacity());
}

TEST(Practice6, SetSize0)
{
    ArrayList<int> arr{3};
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    arr.setSize(4);
    EXPECT_EQ(arr.size(), 3);
}

TEST(Practice6, SetSize1)
{
    ArrayList<int> arr{3};
    arr.insert(arr.size(), 10);
    arr.insert(arr.size(), 11);
    arr.insert(arr.size(), 12);
    arr.setSize(2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(Practice8, EqualityCompareTrue)
{
    ArrayList<int> arr1{3};
    arr1.insert(arr1.size(), 10);
    arr1.insert(arr1.size(), 11);
    arr1.insert(arr1.size(), 12);
    ArrayList<int> arr2{3};
    arr2.insert(arr2.size(), 10);
    arr2.insert(arr2.size(), 11);
    arr2.insert(arr2.size(), 12);
    EXPECT_TRUE(arr1==arr2);
}

TEST(Practice8, EqualityCompareFalse)
{
    ArrayList<int> arr1{3};
    arr1.insert(arr1.size(), 10);
    arr1.insert(arr1.size(), 11);
    arr1.insert(arr1.size(), 12);
    ArrayList<int> arr2{3};
    arr2.insert(arr2.size(), 10);
    arr2.insert(arr2.size(), 11);
    arr2.insert(arr2.size(), 1);
    EXPECT_FALSE(arr1==arr2);
}

TEST(Practice9, InequalityCompareFalse)
{

}

TEST(Practice9, InequalityCompareTrue)
{

}

