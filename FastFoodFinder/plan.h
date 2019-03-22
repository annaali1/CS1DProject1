#ifndef PLAN_H
#define PLAN_H
#include "mainwindow.hpp"
#include <queue>

class Plan
{
public:
    Plan();

private:
    queue<Restaurant> plan;
    double totalDistance;
    double totalRevenue;
};

#endif // PLAN_H
