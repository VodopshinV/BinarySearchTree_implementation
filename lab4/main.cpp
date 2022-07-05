#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>

#include"BinarySearchTree.h"

using namespace std;

//довжина ключа
const int key_length = 12;

uint64_t KeyRandomize();
bool testBinarySearchTree();

int main()
{
    testBinarySearchTree();
    return 0;
}


/*Визначення функції тестування*/
bool testBinarySearchTree()
{
    srand(time(nullptr));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Food> food(keysAmount);
    vector<Food> foodToInsert(iters);
    vector<Food> foodToErase(iters);
    vector<Food> foodToFind(iters);
    vector<pair<Food, Food>>
        foodToRangeQueries;
    for (int i = 0; i < iters; i++)
    {
        foodToInsert[i] = food[KeyRandomize() % keysAmount];
        foodToErase[i] = food[KeyRandomize() % keysAmount];
        foodToFind[i] = food[KeyRandomize() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Food minData = Food();
        Food maxData = Food();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        foodToRangeQueries.push_back(pair<Food, Food>(minData, maxData));
    }
    BinarySearchTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(foodToInsert[i]);
    }
    int myInsertSize = myTree.getSize();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(foodToErase[i]);
    }
    int myEraseSize = myTree.getSize();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(foodToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    set<Food> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(foodToInsert[i]);
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(foodToErase[i]);
    }
    int stlEraseSize = stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(foodToFind[i]) != stlTree.end())
            stlFoundAmount++;
    }

    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {

        myRangeFoundAmount += myTree.findInRange(foodToRangeQueries[i].first,
            foodToRangeQueries[i].second)
            .size();
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(foodToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(foodToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree height: " << myTreeHeight << ", optimal height = " << optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ",found amount: "
        << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount
        << endl
        << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl
        << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

uint64_t KeyRandomize()
{
    uint64_t key = 0;

    for (int i = 0; i < key_length - 1; i++)
    {
        key += (rand() % 10) * pow(10, i);
    }
    key += (rand() % 9 + 1) * pow(10, key_length - 1);

    return key;
}