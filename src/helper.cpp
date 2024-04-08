#include "../include/helper.hpp"

int random_number(int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max);
    return dis(gen);
}