#pragma once
#include<iostream>

/*���������� ��������� ����� Food(���)*/
struct Food
{
public:
    int proteins;      // proteins(����)
    int carbohydrates; // carbohydrates(���������)
    int fats;          // fats(����)

    Food();
    Food(int proteins, int carbohydrates, int fats);

    friend bool operator<(Food const& left_value, Food const& right_value);
    friend bool operator==(Food const& left_value, Food const& right_value);
};
