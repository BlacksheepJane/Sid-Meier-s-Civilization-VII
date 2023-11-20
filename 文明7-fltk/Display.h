#ifndef DISPLAY_H
#define DISPLAY_H

#include "Controller.h"
#include"Letterform.h"

class Display
{
public:
    Display();//��ʼ��

    ~Display();//����

    void DrawMap(Grid* grid,Controller* controller);//��ʾ���е�ͼ

    int DrawAttributes(Controller* controller,Grid* grid);//�����˿�������ʾ�������ԡ��˿��������˷ֲ�

    void DrawWorkersChange(Controller* controller, Grid* grid,int workersNum = 0);//��ʾ����λ�øı䡢������Ҹı乤�˷ֲ�

    void DrawProduction(Controller* controller, Building** buildings,Activity** activities);//Ŀǰ�������������ܸı䵱ǰ����������

    void MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities);

protected:

private:
    int workerspop;
    int *workerscell;
    int prodtype;
    Cell* prodcell;
};

#endif // DISPLAY_H
