#pragma once

#include <vector>
#include <map>

#include "Classes.h"

using namespace std;

class Schedule {
    using Schedule_Per_Group = map<Day, vector<Class>>;
public:
    map<Group, Schedule_Per_Group> schedule;
};