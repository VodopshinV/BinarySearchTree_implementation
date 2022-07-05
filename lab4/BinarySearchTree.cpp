#include"BinarySearchTree.h"

/*Визначення методів бінарного дерева пошуку*/
void BinarySearchTree::insert(Food food)
{
    if (root == nullptr)
    {
        root = new Node(food);
        ++treeSize;
        return;
    }
    else if (insert(root, food))
    {
        ++treeSize;
    }
}

bool BinarySearchTree::find(Food food_to_find)
{
    bool was_found = findNode(root, food_to_find);
    return was_found;
}

void BinarySearchTree::erase(Food food_to_erase)
{
    bool wasDeleted;

    erase(root, food_to_erase, wasDeleted);

    if (wasDeleted)
    {
        --treeSize;
    }
}

Node* BinarySearchTree::findMinObject(Node* node)
{
    while (node->left_node)
    {
        node = node->left_node;
    }

    return node;
}

Node* BinarySearchTree::findMaxObject(Node* node)
{
    while (node->right_node)
    {
        node = node->right_node;
    }

    return node;
}

bool BinarySearchTree::insert(Node* node, Food newFood)
{

    if (newFood < node->food)
    {
        if (!node->left_node)
        {
            node->left_node = new Node(newFood);
            return true;
        }
        return insert(node->left_node, newFood);
    }

    if (node->food < newFood)
    {
        if (!node->right_node)
        {
            node->right_node = new Node(newFood);
            return true;
        }
        return insert(node->right_node, newFood);
    }

    return false;
}

Node* BinarySearchTree::erase(Node* node, Food food_to_erase, bool& wasDeleted)
{
    wasDeleted = false;

    if (node == nullptr)
    {
        return node;
    }

    if (food_to_erase < node->food)
    {
        node->left_node = erase(node->left_node, food_to_erase, wasDeleted);
    }
    else if (node->food < food_to_erase)
    {
        node->right_node = erase(node->right_node, food_to_erase, wasDeleted);
    }
    else
    {
        if (!node->left_node && !node->right_node)
        {
            delete node;
            node = nullptr;
        }
        else if (!node->left_node)
        {
            Node* node_to_delete = node;
            node = node->right_node;
            delete node_to_delete;
        }
        else if (!node->right_node)
        {
            Node* node_to_delete = node;
            node = node->left_node;
            delete node_to_delete;
        }
        else
        {
            Node* node_to_delete = findMinObject(node->right_node);
            node->food = node_to_delete->food;
            node->right_node = erase(node->right_node, node_to_delete->food, wasDeleted);
        }

        wasDeleted = true;
    }
    return node;
}

Node* BinarySearchTree::findNode(Node* node, Food food_to_find)
{
    if (!node || node->food == food_to_find)
        return node;
    if (food_to_find < node->food)
        return findNode(node->left_node, food_to_find);
    else
        return findNode(node->right_node, food_to_find);
}

size_t BinarySearchTree::height(Node* node)
{
    if (!node)
    {
        return 0;
    }

    size_t height_left = height(node->left_node);
    size_t height_right = height(node->right_node);

    if (height_left > height_right)
    {
        return height_left + 1;
    }
    return height_right + 1;
}

std::vector<Food> BinarySearchTree::findInRange(Food minObject, Food maxObject)
{
    std::vector<Food> food_to_find;
    food_to_find.clear();

    findInRange(root, minObject, maxObject, food_to_find);

    return food_to_find;
}

void BinarySearchTree::findInRange(Node* node, Food minObject, Food maxObject, std::vector<Food>& food_to_find)
{
    if (!node)
    {
        return;
    }

    if ((minObject < node->food || minObject == node->food) && (node->food < maxObject || node->food == maxObject))
    {
        food_to_find.push_back(node->food);
    }

    if (minObject < node->food)
    {
        findInRange(node->left_node, minObject, maxObject, food_to_find);
    }

    if (node->food < maxObject)
    {
        findInRange(node->right_node, minObject, maxObject, food_to_find);
    }

}

void BinarySearchTree::print(Node* node)
{
    if (!node)
    {
        return;
    }

    print(node->left_node);

    std::cout << "Food info:" << std::endl;
    std::cout << "Proteins amount: \t" << node->food.proteins << std::endl;
    std::cout << "Carbonhydrates amount: \t" << node->food.carbohydrates << std::endl;
    std::cout << "Fats amount: \t" << node->food.fats << std::endl;

    print(node->right_node);
}

void BinarySearchTree::print()
{
    print(root);
}

