#ifndef GRID_H
#define GRID_H
#include "Building.h"

// this enumerate type represents if the cell is a wild area or owned by a city, or covered with population
enum Civilized { WILD = 0, OWNED, COLONIZED };

struct Cell {
    Landform landform = PLAIN;//����     �����
    Civilized Pop = WILD;   // whether the cell has population�˿ڼ��Ƿ�ӵ�д˵� 
    Building* buildingType = nullptr;//Ĭ��û�� 
    float prodAccumulated = 0.0;//�Ѿ����ѵ��������� 
    float nowprodSpent = 0.0;
    Cell() {}
    Cell(Landform landform) :landform(landform) {}
    ~Cell() {}
};

class Grid//������ͼ 
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
    Cell** grid;//cell��ά���� 
    int grid_m[405];//��ͼ���������400���£����Ըߣ������ڴ���������
    int height, width;//���� 
};

#endif // GRID_H
