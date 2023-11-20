#ifndef DISPLAY_H
#define DISPLAY_H

#include "Controller.h"
#include"Letterform.h"

class Display
{
public:
    Display();//初始化

    ~Display();//析构

    void DrawMap(Grid* grid,Controller* controller);//显示城市地图

    int DrawAttributes(Controller* controller,Grid* grid);//返回人口数，显示各项属性、人口数、工人分布

    void DrawWorkersChange(Controller* controller, Grid* grid,int workersNum = 0);//显示工人位置改变、允许玩家改变工人分布

    void DrawProduction(Controller* controller, Building** buildings,Activity** activities);//目前的生产力，接受改变当前生产力输入

    void MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities);

protected:

private:
    int workerspop;
    int *workerscell;
    int prodtype;
    Cell* prodcell;
};

#endif // DISPLAY_H
