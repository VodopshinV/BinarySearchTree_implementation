#include"Food.h"

/*Визначення методів та операторів структури Food*/
Food::Food()
{
    proteins = rand() % 100;
    carbohydrates = rand() % 100;
    fats = rand() % 100;
}

Food::Food(int proteins, int carbohydrates, int fats)
{
    proteins = proteins;
    carbohydrates = carbohydrates;
    fats = fats;
}

bool operator==(Food const& left_value, Food const& right_value)
{
    return left_value.proteins == right_value.proteins && left_value.carbohydrates == right_value.carbohydrates &&
        left_value.fats == right_value.fats;
}

bool operator<(Food const& left_value, Food const& right_value)
{
    if (left_value.proteins != right_value.proteins)
        return left_value.proteins < right_value.proteins;
    else if (left_value.carbohydrates != right_value.carbohydrates)
        return left_value.carbohydrates < right_value.carbohydrates;
    else
        return left_value.fats < right_value.fats;
}