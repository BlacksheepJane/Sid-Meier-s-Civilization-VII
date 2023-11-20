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
    this->height = this->width = 0;//��ͼ��ʼ��Ϊ 0 0
}

Grid::Grid(const char* filename){//��ʼ������(grid.landform)
    // todo: open the file, read it and save the data to this->grid
   
    
    char line[5];//�ַ����飬���ڶ�ȡ,�������ÿ�ζ�ȡ������������4���ַ�
    int i = 0;
    ifstream infile;
    infile.open(filename);//���ļ�
    if (!infile)
    {
        cout << "�޷����ļ���" << endl;
        exit(1);
    }


    
    //��ʼ�� grid_m[i]
    while (infile.getline(line, 5, ' '))
    {
        this->grid_m[i] = stoi(line);//string to int�����������grid_m[405]��
        i++;
    }



    this->height = this->grid_m[0];//��ʼ�� height width
    this->width = this->grid_m[1];



    this->grid = new Cell* [this->height];//��ʼ�� grid
    for (int i = 0; i < 20; i++)
        this->grid[i] = new Cell[this->width];



    for (i = 0; i < this->height; i++)//��ʼ�� grid.landform
        for (int j = 0; j < this->width; j++) {
            grid[i][j].landform = (Landform)grid_m[20 * i + j + 2];
        }
    infile.close();//�ر��ļ�


}

Grid::~Grid()
{
    //delete this->grid
    for(int i = 0; i < this->height; i++)
        delete [] this->grid[i];
    delete [] this->grid;
}
void bulidingcolor(Building* buildingType) {//����buildingType��color
    /*
        ѧԺblue
        ��Ժpink
        ��ҵ԰yellow
        ���red
        ������cyan
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

//��� һ������һ���� 
//��һ�����ֱ�ʾ�������� �� ɽ���н������Ϊ������ɫ
//���ʾռ�죬���ʾ���˿ڴ��ڣ���ɫ��ʾ�������ڽ��죬������ɺ��Ϊ����ͬɫ
void Grid::getRepresent(int m, int n){
    //����
    Landform Landform = grid[m][n].landform;

    bulidingcolor(grid[m][n].buildingType);//���ݽ������ͱ�ɫ
    cout << landformNames[Landform];
    Letterform::SetColor("white");//�ָ���ɫ


    //��
    Civilized Civilized = grid[m][n].Pop;

    if (!grid[m][n].prodAccumulated) Letterform::SetColor("green"); //������green
    else bulidingcolor(grid[m][n].buildingType);//�����н����뽨��ͬɫ���޽�������ɫ

    switch (Civilized) {
    case 0: {

        cout << " ";
        break; }//δռ��

    case 1: {//ռ��
        cout << "��";
        break;
    }
    case 2: {//����
        cout << "��";
        break;
    }
    }
    Letterform::SetColor("white");//�ָ���ɫ
}


Cell** Grid::getGrid(){
    return this->grid;//�����ͼ�Ķ�ά����
}

int Grid::getGridHeight(){
    return this->height;//��ͼ��
}

int Grid::getGridWidth(){
    return this->width;//��ͼ��
}
