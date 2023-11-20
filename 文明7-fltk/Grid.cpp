#include "Grid.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include"Letterform.h"
using namespace std;
Grid::Grid()
{
    //default constructor is optional
    this->height = this->width = 0;//地图初始化为 0 0
}

Grid::Grid(const char* filename){//初始化地形(grid.landform)
    // todo: open the file, read it and save the data to this->grid
   
    
    char line[5];//字符数组，用于读取,这里假设每次读取的整数不超过4个字符
    int i = 0;
    ifstream infile;
    infile.open(filename);//打开文件
    if (!infile)
    {
        cout << "无法打开文件！" << endl;
        exit(1);
    }


    
    //初始化 grid_m[i]
    while (infile.getline(line, 5, ' '))
    {
        this->grid_m[i] = stoi(line);//string to int，存放在数组grid_m[405]中
        i++;
    }



    this->height = this->grid_m[0];//初始化 height width
    this->width = this->grid_m[1];



    this->grid = new Cell* [this->height];//初始化 grid
    for (int i = 0; i < 20; i++)
        this->grid[i] = new Cell[this->width];



    for (i = 0; i < this->height; i++)//初始化 grid.landform
        for (int j = 0; j < this->width; j++) {
            grid[i][j].landform = (Landform)grid_m[20 * i + j + 2];
        }
    infile.close();//关闭文件


}

Grid::~Grid()
{
    //delete this->grid
    for(int i = 0; i < this->height; i++)
        delete [] this->grid[i];
    delete [] this->grid;
}
void bulidingcolor(Building* buildingType) {//根据buildingType加color
    /*
        学院blue
        剧院pink
        工业园yellow
        奇观red
        市中心cyan
        */
    if (buildingType == nullptr);
    else {
        char* buildingname = buildingType->name;//??
        if (!strcmp(buildingType->name, "cen")) Letterform::SetColor("cyan");
        if (!strcmp(buildingType->name, "cam")) Letterform::SetColor("blue");
        if (!strcmp(buildingType->name, "the")) Letterform::SetColor("pink");
        if (!strcmp(buildingType->name, "won")) Letterform::SetColor("red");
        if (!strcmp(buildingType->name, "ind")) Letterform::SetColor("yellow");
    }
    return;
}

//输出 一个汉字一个○ 
//第一个汉字表示地形类型 如 山，有建筑则变为建筑颜色
//○表示占领，●表示有人口存在，绿色表示建筑正在建造，建造完成后变为建筑同色
void Grid::getRepresent(int m, int n){
    //地形
    Landform Landform = grid[m][n].landform;

    bulidingcolor(grid[m][n].buildingType);//根据建筑类型变色
    cout << landformNames[Landform];
    Letterform::SetColor("white");//恢复白色


    //人
    Civilized Civilized = grid[m][n].Pop;

    if (!grid[m][n].prodAccumulated) Letterform::SetColor("green"); //建造中green
    else bulidingcolor(grid[m][n].buildingType);//否则有建筑与建筑同色，无建筑不变色

    switch (Civilized) {
    case 0: {

        cout << " ";
        break; }//未占据

    case 1: {//占据
        cout << "○";
        break;
    }
    case 2: {//有人
        cout << "●";
        break;
    }
    }
    Letterform::SetColor("white");//恢复白色
}


Cell** Grid::getGrid(){
    return this->grid;//代表地图的二维数组
}

int Grid::getGridHeight(){
    return this->height;//地图长
}

int Grid::getGridWidth(){
    return this->width;//地图宽
}
