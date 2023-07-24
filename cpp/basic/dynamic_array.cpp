#include <vector>

#include "my_vector.h"

using namespace std;

TEST(dynamic_array, iterator_length)
{
    vector<int> arr;
    auto        ret = arr.end() - arr.begin();

    EXPECT_EQ(ret, 0);
    cout << typeid(decltype(ret)).name() << endl; // msve.cpp17:__int64

    arr = {1};
    EXPECT_EQ(arr.end() - arr.begin(), 1);

    arr = {2, 2};
    EXPECT_EQ(arr.end() - arr.begin(), 2);

    arr = {1, 2, 3};
    {
        auto iter = std::find(arr.begin(), arr.end(), 1);
        EXPECT_EQ(iter - arr.begin(), 0); // if (iter != arr.end())

        iter = std::find(arr.begin(), arr.end(), 2);
        EXPECT_EQ(iter - arr.begin(), 1); // if (iter != arr.end())
    }
}
