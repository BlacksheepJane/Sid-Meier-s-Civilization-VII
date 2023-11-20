#ifndef CONTROLLER_H
#define CONTROLLER_H

#define TOTAL_ROUND (100)

#define PRODUCTION_TYPE_BUILDING (1)
#define PRODUCTION_TYPE_ACTIVITY (2)
#include<vector>
#include "Grid.h"

class Controller
{
    public:
        Controller();

        virtual ~Controller();

        bool bindGrid(Grid* grid);

        bool nextRound(int &newX, int &newY, float &nextThres);

        int checkPop();
        std::vector<Activity*>availableActivities;
       //activity指针数组
        int activitySize = 0;

        bool SetProductionBuilding(int m, int n, Building* Building);
        bool SetProductionActivity(Activity* activity);
        bool SetProductionActivity(int activityOrder);

        int setPopAt(int m, int n, bool isAdding=true);

        Attributes getAttributes();

        int getPop();
        int getWorkingPop(int &workersNumber, int *&workersCellCoords);

        Production* getProduction(int &productionType, Cell *&currentProductionCell);

        void getCellDescription(int m, int n);

        int getRound();

        void reset(int pop, float firstBorderThreshold = 5.0);

        int checkBorderUpdate(int &newX, int &newY);

    protected:

    private:
        Attributes currentAttributes;//当前属性

        float pop;//人口数

        int workingPop;//已经工作的人口数

        float BorderExpandThreshold = 0.0;//扩地所需要的文化值

        int currentRound;//当前回合

        Production* currentProduction;//当前生产
        int currentProductionType = 0;//building or activity
        Cell* currentProductionCell = 0;//现在生产所处地块

        Grid *world;//地图

        int updateProduction();

        void updatePop();

        void updateAttributes();

        bool checkWin();

        Cell** getAdjacentCells(int m, int n);

        int getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType);
        int wonn=0;//奇观数
};

#endif // CONTROLLER_H
