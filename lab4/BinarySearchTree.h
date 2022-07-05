#pragma once
#include"Food.h"

#include<vector>

struct Node
{
public:
    Food food;
    Node* right_node;
    Node* left_node;

    Node(Food food_obj)
    {
        food = food_obj;
        right_node = nullptr;
        left_node = nullptr;
    }
};


/*Оголошення Бинарного дерева пошуку*/
struct BinarySearchTree
{
private:
    Node* root;
    size_t treeSize;

public:
    BinarySearchTree() { root = nullptr; treeSize = 0; }
    void insert(Food food);
    bool find(Food food);
    void erase(Food food);
    size_t getSize() { return treeSize; }
    void print();
    void print(Node* node);
    size_t height() { return height(root); }
    size_t height(Node* node);
    std::vector<Food> findInRange(Food minObject, Food maxObject);
    void findInRange(Node* node, Food minObject, Food maxObject, std::vector<Food>& food_to_find);
    Node* findMinObject(Node* node);
    Node* findMaxObject(Node* node);
    bool insert(Node* node, Food food);
    Node* erase(Node* node, Food food, bool& wasDeleted);
    Node* findNode(Node* node, Food food);
};