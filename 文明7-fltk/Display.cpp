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
                    controller->getCellDescription((i - 3) / 2, (j - 3) / 2);// grid->getGrid()[(i - 3) / 2][(j - 3) / 2].landform;//需要调试一下，不能确定是否对应上了
                }
            }
        }
        cout << endl;
    }

    // todo: draw the map
}

int Display::DrawAttributes(Controller* controller,Grid* grid) {
    cout << "人口值为：" << controller->getPop() << endl
        << "粮食数为：: " << controller->getAttributes().food << endl
        << "科技值为: " << controller->getAttributes().tech << endl
        << "文化值为: " << controller->getAttributes().cul << endl
        << "生产力为：: " << controller->getAttributes().prod << endl;
    controller->getWorkingPop(workerspop, workerscell);
    cout << "是否查看工作人口数和工人分布？ 按 Y 或 N" << endl;
    char get;
    cin >> get;
    if (get == 'Y')
    {
        cout << "工作人口数为：" << this->workerspop << endl;
        int cur = 0;
        cout << "提示：有工人的位置显示红色，否则显示白色！" << endl;
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
    cout << "工人分布如下：" << endl;
    int j = 1;
    for (int i = 0; i < 2 * workerspop; i++)
    {
        cout << "第" << j << "名工人的位置是： " << "(" << workerscell[i] << "," << workerscell[++i] << ")";
        ++j;
    }
    cout << "选择是否要改变工人分布的位置？" << endl;
    cout << "Y:是的，我要改变！" << endl;
    cout << "N:不是，我再想想！" << endl;
    char get;
    cin >> get;
    if (get != 'Y' && get != 'N') { cout << "错误输入！"; return DrawWorkersChange(controller,grid,pop); }
    else if (get == 'Y')
    {
        int choice;
        do {
            cout << "请选择你要操作的类型：" << endl;
            cout << "想要增加工人数量？请按1！" << endl;
            cout << "想要减少工人数量？请按2！" << endl;
            cout << "想要改变工人分布位置？请按3！" << endl;
            cout << "你的选择是：";
            cin >> choice;
            cout << endl;
            if (choice != 1 && choice != 2 && choice != 3)
                cout << "操作失败，请重试！" << endl;
        } while (choice != 1 && choice != 2 && choice != 3);

        switch (choice) {
        case 1: {
            int add1, add2;
            do {
                cout << "选择你想增加工人的起始位置：" << endl;
                cout << "请选择你想增加的工人所在的行数："; cin >> add1; cout << endl;
                cout << "请选择你想增加的工人所在的列数："; cin >> add2; cout << endl;
                if (controller->setPopAt(add1, add2, 1) == -1)  
                    cout << "操作失败，请重试！" << endl; 
            } while (controller->setPopAt(add1, add2, 1) == -1);
            controller->setPopAt(add1, add2, 1);
            break;
        }
        case 2: {
            int reduce1, reduce2;
            do{
                cout << "选择你想减少工人的起始位置：" << endl;
                cout << "请选择你想减少的工人所在的行数："; cin >> reduce1; cout << endl;
                cout << "请选择你想减少的工人所在的列数："; cin >> reduce2; cout << endl;
                controller->setPopAt(reduce1, reduce2, 0);
                if (controller->setPopAt(reduce1, reduce2, 0) == -1)
                    cout << "操作失败，请重试！" << endl;
            } while (controller->setPopAt(reduce1, reduce2, 0) == -1);
            break;
        }
        case 3: {
            bool flag = 0;
            int x = 0, y = 0, m = 0, n = 0;
            for (flag; flag == 0;) {

                cout << "选择你想转移工人的起始位置：" << endl;
                cout << "请选择你想转移工人初始所在的行数："; cin >> x; cout << endl;
                cout << "请选择你想转移工人初始所在的列数："; cin >> y; cout << endl;
                cout << "你想把（" << x << "," << y << "）处的工人转移到哪儿？" << endl;
                cout << "请选择你想把工人转移到的行数："; cin >> m; cout << endl;
                cout << "请选择你想把工人转移到的列数："; cin >> n; cout << endl;
                if (m < 0 || n < 0 || m >= grid->getGridHeight() || n >= grid->getGridWidth()) { cout << "输入错误！请重试！" << endl; }
                else flag = 1;
            }
            controller->setPopAt(x, y, 0);
            controller->setPopAt(m, n, 1);
            break;
        }
        default:cout << "选择错误！" << endl;
        }
        return DrawWorkersChange(controller, grid, pop);
    }
    else return;
}

//Building** buildings = new Building * [5]{ center, campus, theatre, wonder, industrialPark };
void Display::DrawProduction(Controller* controller, Building** buildings,Activity** activities) {
    //显示上一个回合中
    
    //进行生产变更操作
    controller->getProduction(prodtype, prodcell);
    cout << "请输入您想操作的格子坐标： " << endl;
    int m, n;
    cin >> m >> n;
   
    //想做活动还是想造建筑？
    int a;
    do{cout << "您想要进行建筑还是举办活动？" << endl;
    cout << "如果您想要进行建筑操作，请按1！" << endl;
    cout << "如果您想要举办活动，请按2！" << endl;
    cin >> a;
    if (a != 1 && a != 2)
        cout << "操作失败，请重试！" << endl;
    } while (a != 1 && a != 2);
   
    switch (a) {
        //造建筑
    case 1: cout << "您选择进行建筑操作！" << endl;
        cout << "您想要建哪种类型的建筑？" << endl;
        cout << "学院： A  剧院： B  奇观： C  工业园： D  " << endl;
        char get;
        do {
            cin >> get;
            switch (get) {
            case 'A':if (controller->SetProductionBuilding(m, n, buildings[1]))cout << "操作成功！" << endl; else cout << "操作失败！" << endl; break;
            case 'B':if (controller->SetProductionBuilding(m, n, buildings[2]))cout << "操作成功！"<<endl; else cout << "操作失败！" << endl; break;
            case 'C':if (controller->SetProductionBuilding(m, n, buildings[3]))cout << "操作成功！"<<endl; else cout << "操作失败！" << endl; break;
            case 'D':if (controller->SetProductionBuilding(m, n, buildings[4]))cout << "操作成功！"<<endl; else cout << "操作失败！" << endl; break;
                if (get != 'A' && get != 'B' && get != 'C' && get != 'D')
                    cout << "操作失败，请重试！" << endl;
            }
        } while (get != 'A' && get != 'B' && get != 'C' && get != 'D');
        break;
       //举办活动
    case 2: cout << "您选择举办活动！" << endl;
        cout << "您想要举办哪种类型的活动？" << endl;
        cout << "学术会议： A;漫展： B；工业物流： C" << endl;
        char get2;
        do {
            cin >> get2;
            switch (get2) {
            case'A':if (controller->SetProductionActivity(activities[0]))cout << "操作成功！" << endl; else cout << "操作失败！"<<endl; break;
            case'B':if (controller->SetProductionActivity(activities[1]))cout << "操作成功！" << endl; else cout << "操作失败！"<<endl; break;
            case'C':if (controller->SetProductionActivity(activities[2]))cout << "操作成功！" << endl; else cout << "操作失败！"<<endl; break;
                if (get2 != 'A' && get2 != 'B' && get2 != 'C')
                    cout << "操作失败，请重试！" << endl;
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
    cout << "选择城市中心位置" << endl;
    cout << "请选择目标位置所在行： "; cin >> x; cout << endl;
    cout << "请选择目标位置所在列： "; cin >> y; cout << endl;
    controller->SetProductionBuilding(x, y, buildings[0]);
    while (true) {
        int newX, newY;
        cout << "请选择需要扩地的位置：" << endl;
        cout << "请选择目标位置所在行： "; cin >> newX;
        cout << "请选择目标位置所在列： "; cin >> newY;
        float nextThres;
        if (controller->nextRound(newX, newY, nextThres)) {
            cout << "你赢了！" << endl;
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