#ifndef BUILDING_H
#define BUILDING_H
#include "Attributes.h"
#include "Activity.h"

enum Landform{OCEAN=0, SEA, PLAIN, HILLY, DESERT, MOUNTAIN, NOTYPE};
// this constant two-dimension array represents landform buffs on food and productivity respectively
static int landformBuffs[7][2] = {
    {1, 0}, {1, 1}, {2, 1}, {2, 2}, {0, 1}, {0, 0}, {0, 0}
}; //土地上有人工作时的粮食、生产力加成 
static const char* landformNames[7] = {
    "深", "近", "平", "丘", "沙", "山", "无"//深海 近海 平原 丘陵 沙漠 山脉 无
};

class Building: public Production//派生类，可以理解为将public的属性都加到building里面了 
{
    public:
        Building();
        Building(char* name, float prodSpent, Attributes basicBonus, Attributes popBonus, Attributes locationBonus, char* locationBonusTargetBuildings, Landform locationBonusTargetLandform, Activity* activity=0);
        ~Building();

        // this array represents the basic bonus on 4 aspects: tech, cul, food, prod
        Attributes basicBonus;

        // this array represents the bonus related to population on those 4 aspects
        Attributes popBonus;

        // this array represents the bonus of adjacent location on those 4 aspects
        Attributes locationBonus;
        char* locationBonusTargetBuildings;//相邻建筑加成 
        Landform locationBonusTargetLandform;//相邻地块加成 

        Activity* activity;//可进行的项目 
};

#endif // BUILDING_H
