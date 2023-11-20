#ifndef GRID_H
#define GRID_H
#include "Building.h"

// this enumerate type represents if the cell is a wild area or owned by a city, or covered with population
enum Civilized { WILD = 0, OWNED, COLONIZED };

struct Cell {
    Landform landform = PLAIN;//地形     已完成
    Civilized Pop = WILD;   // whether the cell has population人口及是否拥有此地 
    Building* buildingType = nullptr;//默认没有 
    float prodAccumulated = 0.0;//已经花费的生产力？ 
    float nowprodSpent = 0.0;
    Cell() {}
    Cell(Landform landform) :landform(landform) {}
    ~Cell() {}
};

class Grid//整个地图 
{
public:
    Grid();
    
    Grid(const char* filename);

    ~Grid();

    Cell** getGrid();

    int getGridHeight();
    int getGridWidth();

    void getRepresent(int m, int n);

protected:

private:
    Cell** grid;//cell二维数组 
    int grid_m[405];//地图面积限制在400以下（可以高，但是内存可能溢出）
    int height, width;//长宽 
};

#endif // GRID_H
