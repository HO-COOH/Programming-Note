#include "Range/Range.hpp"
#include "IO/IO.hpp"
#include <utility>
#include <array>

template <typename T>
constexpr auto partition(T &array, int left, int right)
{
    auto i = left;
    auto &pivot = array[right];
    for (auto j : Range(left, right))
    {
        if (array[j] <= pivot)
        {
            std::swap(array[i], array[j]);
            ++i;
        }
    }
    std::swap(array[i], pivot);
    return i;
}

template <typename T>
constexpr void quickSort(T &array, int left, int right)
{
    if (left < right)
    {
        auto q = partition(array, left, right);
        quickSort(array, left, q - 1);
        quickSort(array, q + 1, right);
    }
}