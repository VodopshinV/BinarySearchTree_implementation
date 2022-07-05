#pragma once
#include<iostream>

/*Оголошення структури даних Food(їжа)*/
struct Food
{
public:
    int proteins;      // proteins(білки)
    int carbohydrates; // carbohydrates(вуглеводи)
    int fats;          // fats(жири)

    Food();
    Food(int proteins, int carbohydrates, int fats);

    friend bool operator<(Food const& left_value, Food const& right_value);
    friend bool operator==(Food const& left_value, Food const& right_value);
};
