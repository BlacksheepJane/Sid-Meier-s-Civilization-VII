#include "Display.h"
#include<iostream>

using namespace std;

Display::Display()
{
    
    //ctor
}

Display::~Display()
{
    //dtor
}

void Display::DrawMap(Grid* grid,Controller *controller) {
    for (int i = 0; i <= 2*grid->getGridHeight() + 2; i++)
    {
        for (int j = 0; j <= 2*grid->getGridWidth() + 2; j++)
        {
            if (i % 2 == 0) { cout << "__"; }
            else {
                if (j % 2 == 0) { cout << "|"; }
                else {
                    if (i == 1 && j == 1) { cout << "   "; continue; }
                    if (i == 1) { if(j<23)cout << (j - 3) / 2<<"  "; else cout << (j - 3) / 2<<" "; continue; }
                    if (j == 1) { if (i < 23)cout << (i - 3) / 2 << "  "; else cout << (i - 3) / 2<<" "; continue; }
                    //switch(grid->getGrid()[(i-3)/2][(j-3)/2].buildingType)
                    controller->getCellDescription((i - 3) / 2, (j - 3) / 2);// grid->getGrid()[(i - 3) / 2][(j - 3) / 2].landform;//��Ҫ����һ�£�����ȷ���Ƿ��Ӧ����
                }
            }
        }
        cout << endl;
    }

    // todo: draw the map
}

int Display::DrawAttributes(Controller* controller,Grid* grid) {
    cout << "�˿�ֵΪ��" << controller->getPop() << endl
        << "��ʳ��Ϊ��: " << controller->getAttributes().food << endl
        << "�Ƽ�ֵΪ: " << controller->getAttributes().tech << endl
        << "�Ļ�ֵΪ: " << controller->getAttributes().cul << endl
        << "������Ϊ��: " << controller->getAttributes().prod << endl;
    controller->getWorkingPop(workerspop, workerscell);
    cout << "�Ƿ�鿴�����˿����͹��˷ֲ��� �� Y �� N" << endl;
    char get;
    cin >> get;
    if (get == 'Y')
    {
        cout << "�����˿���Ϊ��" << this->workerspop << endl;
        int cur = 0;
        cout << "��ʾ���й��˵�λ����ʾ��ɫ��������ʾ��ɫ��" << endl;
        for (int i = 0; i <= grid->getGridHeight() + 2; i++)
        {
            for (int j = 0; j <= grid->getGridWidth() + 2; j++)
            {
                if (i % 2 == 0) { cout << "_"; }
                else {
                    if (j % 2 == 0) { cout << "|"; }
                    else {
                        if (i == 1 && j == 1) { cout << " "; continue; }
                        if (i == 1) { cout << (j - 3) / 2; continue; }
                        if (j == 1) { cout << (i - 3) / 2; continue; }
                        if (i == 3 + 2 * workerscell[cur] && j == 3 + 2 * workerscell[cur + 1])
                        {
                            Letterform::SetColor("red");
                            cout<< grid->getGrid()[(i - 3) / 2][(j - 3) / 2].landform;
                            cur += 2;
                            Letterform::SetColor("white");
                        }
                        else cout << grid->getGrid()[(i - 3) / 2][(j - 3) / 2].landform; 
                    }
                }
            }
            cout << endl;
        }

    }
    return controller->getPop();
    
    // todo: draw the attributes, population, and the distribution of workers, return the population
}

void Display::DrawWorkersChange(Controller* controller, Grid* grid, int pop) {
    cout << "���˷ֲ����£�" << endl;
    int j = 1;
    for (int i = 0; i < 2 * workerspop; i++)
    {
        cout << "��" << j << "�����˵�λ���ǣ� " << "(" << workerscell[i] << "," << workerscell[++i] << ")";
        ++j;
    }
    cout << "ѡ���Ƿ�Ҫ�ı乤�˷ֲ���λ�ã�" << endl;
    cout << "Y:�ǵģ���Ҫ�ı䣡" << endl;
    cout << "N:���ǣ��������룡" << endl;
    char get;
    cin >> get;
    if (get != 'Y' && get != 'N') { cout << "�������룡"; return DrawWorkersChange(controller,grid,pop); }
    else if (get == 'Y')
    {
        int choice;
        do {
            cout << "��ѡ����Ҫ���������ͣ�" << endl;
            cout << "��Ҫ���ӹ����������밴1��" << endl;
            cout << "��Ҫ���ٹ����������밴2��" << endl;
            cout << "��Ҫ�ı乤�˷ֲ�λ�ã��밴3��" << endl;
            cout << "���ѡ���ǣ�";
            cin >> choice;
            cout << endl;
            if (choice != 1 && choice != 2 && choice != 3)
                cout << "����ʧ�ܣ������ԣ�" << endl;
        } while (choice != 1 && choice != 2 && choice != 3);

        switch (choice) {
        case 1: {
            int add1, add2;
            do {
                cout << "ѡ���������ӹ��˵���ʼλ�ã�" << endl;
                cout << "��ѡ���������ӵĹ������ڵ�������"; cin >> add1; cout << endl;
                cout << "��ѡ���������ӵĹ������ڵ�������"; cin >> add2; cout << endl;
                if (controller->setPopAt(add1, add2, 1) == -1)  
                    cout << "����ʧ�ܣ������ԣ�" << endl; 
            } while (controller->setPopAt(add1, add2, 1) == -1);
            controller->setPopAt(add1, add2, 1);
            break;
        }
        case 2: {
            int reduce1, reduce2;
            do{
                cout << "ѡ��������ٹ��˵���ʼλ�ã�" << endl;
                cout << "��ѡ��������ٵĹ������ڵ�������"; cin >> reduce1; cout << endl;
                cout << "��ѡ��������ٵĹ������ڵ�������"; cin >> reduce2; cout << endl;
                controller->setPopAt(reduce1, reduce2, 0);
                if (controller->setPopAt(reduce1, reduce2, 0) == -1)
                    cout << "����ʧ�ܣ������ԣ�" << endl;
            } while (controller->setPopAt(reduce1, reduce2, 0) == -1);
            break;
        }
        case 3: {
            bool flag = 0;
            int x = 0, y = 0, m = 0, n = 0;
            for (flag; flag == 0;) {

                cout << "ѡ������ת�ƹ��˵���ʼλ�ã�" << endl;
                cout << "��ѡ������ת�ƹ��˳�ʼ���ڵ�������"; cin >> x; cout << endl;
                cout << "��ѡ������ת�ƹ��˳�ʼ���ڵ�������"; cin >> y; cout << endl;
                cout << "����ѣ�" << x << "," << y << "�����Ĺ���ת�Ƶ��Ķ���" << endl;
                cout << "��ѡ������ѹ���ת�Ƶ���������"; cin >> m; cout << endl;
                cout << "��ѡ������ѹ���ת�Ƶ���������"; cin >> n; cout << endl;
                if (m < 0 || n < 0 || m >= grid->getGridHeight() || n >= grid->getGridWidth()) { cout << "������������ԣ�" << endl; }
                else flag = 1;
            }
            controller->setPopAt(x, y, 0);
            controller->setPopAt(m, n, 1);
            break;
        }
        default:cout << "ѡ�����" << endl;
        }
        return DrawWorkersChange(controller, grid, pop);
    }
    else return;
}

//Building** buildings = new Building * [5]{ center, campus, theatre, wonder, industrialPark };
void Display::DrawProduction(Controller* controller, Building** buildings,Activity** activities) {
    //��ʾ��һ���غ���
    
    //���������������
    controller->getProduction(prodtype, prodcell);
    cout << "��������������ĸ������꣺ " << endl;
    int m, n;
    cin >> m >> n;
   
    //������������콨����
    int a;
    do{cout << "����Ҫ���н������Ǿٰ���" << endl;
    cout << "�������Ҫ���н����������밴1��" << endl;
    cout << "�������Ҫ�ٰ����밴2��" << endl;
    cin >> a;
    if (a != 1 && a != 2)
        cout << "����ʧ�ܣ������ԣ�" << endl;
    } while (a != 1 && a != 2);
   
    switch (a) {
        //�콨��
    case 1: cout << "��ѡ����н���������" << endl;
        cout << "����Ҫ���������͵Ľ�����" << endl;
        cout << "ѧԺ�� A  ��Ժ�� B  ��ۣ� C  ��ҵ԰�� D  " << endl;
        char get;
        do {
            cin >> get;
            switch (get) {
            case 'A':if (controller->SetProductionBuilding(m, n, buildings[1]))cout << "�����ɹ���" << endl; else cout << "����ʧ�ܣ�" << endl; break;
            case 'B':if (controller->SetProductionBuilding(m, n, buildings[2]))cout << "�����ɹ���"<<endl; else cout << "����ʧ�ܣ�" << endl; break;
            case 'C':if (controller->SetProductionBuilding(m, n, buildings[3]))cout << "�����ɹ���"<<endl; else cout << "����ʧ�ܣ�" << endl; break;
            case 'D':if (controller->SetProductionBuilding(m, n, buildings[4]))cout << "�����ɹ���"<<endl; else cout << "����ʧ�ܣ�" << endl; break;
                if (get != 'A' && get != 'B' && get != 'C' && get != 'D')
                    cout << "����ʧ�ܣ������ԣ�" << endl;
            }
        } while (get != 'A' && get != 'B' && get != 'C' && get != 'D');
        break;
       //�ٰ�
    case 2: cout << "��ѡ��ٰ���" << endl;
        cout << "����Ҫ�ٰ��������͵Ļ��" << endl;
        cout << "ѧ�����飺 A;��չ�� B����ҵ������ C" << endl;
        char get2;
        do {
            cin >> get2;
            switch (get2) {
            case'A':if (controller->SetProductionActivity(activities[0]))cout << "�����ɹ���" << endl; else cout << "����ʧ�ܣ�"<<endl; break;
            case'B':if (controller->SetProductionActivity(activities[1]))cout << "�����ɹ���" << endl; else cout << "����ʧ�ܣ�"<<endl; break;
            case'C':if (controller->SetProductionActivity(activities[2]))cout << "�����ɹ���" << endl; else cout << "����ʧ�ܣ�"<<endl; break;
                if (get2 != 'A' && get2 != 'B' && get2 != 'C')
                    cout << "����ʧ�ܣ������ԣ�" << endl;
            }
        } while (get2 != 'A' && get2 != 'B' && get2 != 'C');
        break;
    }
        
    // todo: draw the current production, and receive the input for changing the current production

}

void Display::MainProcess(Controller* controller, Grid* grid, Building** buildings, Activity** activities) {
    controller->reset(3);
    controller->bindGrid(grid);
    this->DrawMap(grid,controller);
    int x, y;
    cout << "ѡ���������λ��" << endl;
    cout << "��ѡ��Ŀ��λ�������У� "; cin >> x; cout << endl;
    cout << "��ѡ��Ŀ��λ�������У� "; cin >> y; cout << endl;
    controller->SetProductionBuilding(x, y, buildings[0]);
    while (true) {
        int newX, newY;
        cout << "��ѡ����Ҫ���ص�λ�ã�" << endl;
        cout << "��ѡ��Ŀ��λ�������У� "; cin >> newX;
        cout << "��ѡ��Ŀ��λ�������У� "; cin >> newY;
        float nextThres;
        if (controller->nextRound(newX, newY, nextThres)) {
            cout << "��Ӯ�ˣ�" << endl;
            return;
        }
        else if (newX != -1) {
            cout << "Border expanded at (" << newX << ", " << newY << "), when culture reaches " << nextThres << " border will expand again." << endl;
        }
        DrawMap(grid, controller);
        int pop = DrawAttributes(controller,grid);
        DrawProduction(controller, buildings,activities);
        DrawWorkersChange(controller,grid, pop);
        cout << "\n\nRound: " << controller->getRound() << endl;
    }
}