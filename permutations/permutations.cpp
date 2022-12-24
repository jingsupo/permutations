#include <iostream>
#include <vector>

#define __builtin_popcount __popcnt

template<class T>
std::vector<std::vector<T>> Combinations(T set[], int len, int k)
{
    std::vector<std::vector<T>> subsets;
    unsigned int length = len;
    if (k > length)
    {
        k = length;
    }
    for (unsigned int subsetBits = 1; subsetBits < (1 << length); subsetBits++)
    {
        if (k > 0 && __builtin_popcount(subsetBits) != k)
        {
            continue;
        }
        std::vector<T> subset;
        for (unsigned int object = 0; object < length; object++)
        {
            if (((subsetBits >> object) & 1) == 1)
            {
                subset.push_back(set[object]);
            }
        }
        subsets.push_back(subset);
    }
    return subsets;
}

void toNext(std::vector<int> arr, int n, std::vector<std::vector<int>>& dst)
{
    unsigned int length = arr.size();
    if (n == length - 1)
    {
        std::vector<int> tmp;
        std::copy(arr.begin(), arr.end(), std::back_inserter(tmp));
        dst.push_back(tmp);
    }
    for (size_t i = n; i < length; i++)
    {
        int tmp = arr[i];
        arr[i] = arr[n];
        arr[n] = tmp;
        toNext(arr, n + 1, dst);
        tmp = arr[i];
        arr[i] = arr[n];
        arr[n] = tmp;
    }
}

std::vector<std::vector<int>> Permute(std::vector<int> arr)
{
    std::vector<std::vector<int>> ret;
    toNext(arr, 0, ret);
    return ret;
}

std::vector<std::vector<int>> Permutations(int arr[], int len, int k)
{
    std::vector<std::vector<int>> ret;
    auto combs = Combinations(arr, len, k);
    for (auto& v : combs)
    {
        auto res = Permute(v);
        for (auto it = res.begin(); it != res.end(); it++)
        {
            ret.push_back(*it);
        }
    }
    return ret;
}

template<class T>
void printCon(T& t) {
    for (auto it1 = t.begin(); it1 != t.end(); it1++)
    {
        for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int arr[] = { 3, 4, 6, 10, 15, 17 };
    auto len = sizeof(arr) / sizeof(arr[0]);
    auto ret = Combinations(arr, len, 3);
    std::cout << "Combinations: " << ret.size() << "\n";
    printCon(ret);
    ret = Permutations(arr, len, 3);
    std::cout << "Permutations: " << ret.size() << "\n";
    printCon(ret);
}
