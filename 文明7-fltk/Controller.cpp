#include "Controller.h"
#include "cstring"

Controller::Controller()
{
    this->currentRound = 0;
    this->world = 0;
    this->pop = 2;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

Controller::~Controller()
{
    //dtor
}

void Controller::reset(int pop, float firstBorderThreshold){
    this->BorderExpandThreshold = 1;
    this->currentRound = 0;
    this->world = 0;
    this->pop = pop;
    this->workingPop = 0;
    this->currentAttributes = Attributes(0);
}

bool Controller::checkWin(){
    // todo: check whether the player has won the game
    float poi=0.5*(currentAttributes.tech+currentAttributes.cul)+10*pop+currentAttributes.prod;
    if(currentAttributes.tech>=500||currentAttributes.cul>=350&&wonn>=5||poi>=500)
    {

        return 1;
    }

    return false;
}
//绑定地图
bool Controller::bindGrid(Grid* grid){
    this->world = grid;
    return (grid != 0);
}

Attributes Controller::getAttributes(){
    return this->currentAttributes;
}

int Controller::getPop(){
    return this->pop;
}

int Controller::getWorkingPop(int &workersNumber, int *&workersCellCoords){
    workersNumber = this->workingPop;
    if(workersCellCoords != 0) delete [] workersCellCoords;
    if(workersNumber == 0){
        workersCellCoords = 0;
        return 0;
    }
    workersCellCoords = new int[2 * workersNumber]{0};
    Cell** grid = this->world->getGrid();//更新地图
    int m = this->world->getGridHeight(), n = this->world->getGridWidth();
    int cur = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j].Pop == COLONIZED){
                workersCellCoords[cur] = i;
                workersCellCoords[cur + 1] = j;
                cur += 2;
            }
        }
    }//读取每个工作人口位置
    if(cur != workersNumber * 2) return -1;//人口没分配完
    return 0;
}
//读取m，n数据
void Controller::getCellDescription(int m, int n){
    world->getRepresent(m, n);
}
//回合数
int Controller::getRound(){
    return currentRound;
}
//需保证不会两次建造center，这里没有判定
bool Controller::SetProductionBuilding(int m, int n, Building* building){
    // todo: set the current production to building at coordinates (m, n), return true if the action is successful
    if(world->getGrid()[m][n].buildingType!=building&&world->getGrid()[m][n].buildingType!=0)
    {
        return false;
    }
    if(world->getGrid()[m][n].Pop == WILD)
        return 0;
    currentProductionType = currentProductionType;
    world->getGrid()[m][n].buildingType = building;
    currentProductionCell = &(world->getGrid()[m][n]);
    currentProduction = building;
    return 1;
}
//使用时注意要先判定此项活动能不能进行(即是否拥有对应建筑)
bool Controller::SetProductionActivity(Activity* activity){
    // todo: set the current production to activity, return true if the action is successful
    bool flagg = 0;
    for(int i=0;i<activitySize;i++)
            {
                if(availableActivities[i] == activity)
                    flagg = 1;
            }
    if(flagg == 0)
        return 0;
    currentProductionType = PRODUCTION_TYPE_ACTIVITY;
    currentProductionCell = 0;
    currentProduction = activity;


}
bool Controller::SetProductionActivity(int activityOrder){
    if(activityOrder >= activitySize || activityOrder < 0)
        return false;
    currentProductionType = PRODUCTION_TYPE_ACTIVITY;
    currentProductionCell = 0;
    currentProduction = availableActivities[activityOrder];
    return true;
}
//胜利 返回1，否则 返回0，若扩地失败 newX=-1,
bool Controller::nextRound(int &newX, int &newY, float &nextThres){
    // todo: continue to the next round with border expanding at (newX, newY) and next expansion culture threshold nextThres
    updateAttributes();
    updateProduction();
    updatePop();
    currentRound++;
    nextThres = checkBorderUpdate(newX,newY);
    if(checkBorderUpdate(newX,newY)){
        nextThres = checkBorderUpdate(newX,newY);
        world->getGrid()[newX][newY].Pop = OWNED;
    }
    else newX = -1;
     for(int i=0;i<activitySize;i++)
    {
        if(availableActivities[i]->remainingEffectedRounds)
            availableActivities[i]->remainingEffectedRounds--;
    }
    return checkWin();
    /* nextThres*=2
        produpdate

    activity 持续次数--
    */
}
//生产一回合，if完成 return 1，否则 return 0
int Controller::updateProduction(){
    // todo: update the process of current prodution
    if(currentProductionType==PRODUCTION_TYPE_ACTIVITY)
    {
        ((Activity*)currentProduction)->prodAccumulated+=currentAttributes.prod;
        if(((Activity*)currentProduction)->prodAccumulated>=((Activity*)currentProduction)->nowprodSpent)
        {
            ((Activity*)currentProduction)->prodAccumulated=0;
            ((Activity*)currentProduction)->remainingEffectedRounds = ((Activity*)currentProduction)->effectedRounds;
            currentProductionType = 0;
            return 1;
        }
    }
    else if(currentProductionType==PRODUCTION_TYPE_BUILDING)
    {
        currentProductionCell->prodAccumulated+=currentAttributes.prod;
     if(currentProductionCell->prodAccumulated>=currentProductionCell->nowprodSpent)
        {
            currentProductionCell->prodAccumulated = 0;
            currentProductionType = 0;
            bool flagg=1;
            for(int i=0;i<activitySize;i++)
            {
                if(availableActivities[i] == currentProductionCell->buildingType->activity)
                    flagg = 0;
            }
            if(flagg)
            {
                availableActivities.push_back(currentProductionCell->buildingType->activity);
                activitySize++;
            }
            return 1;
        }
    //availableactivity need to be change
    }
    return 0;

}
//获得当前生产各项信息
Production* Controller::getProduction(int &productionType, Cell *&currentProductionCell){
    productionType = this->currentProductionType;
    currentProductionCell = this->currentProductionCell;
    return this->currentProduction;
}

//检测人口是否安排完，回合结束时需要检查。
int Controller::checkPop(){
    if(int(this->workingPop) > this->pop)
        return -1;  //you have to remove pops
    else if(int(this->workingPop) < this->pop)
        return 1;   //you may add pops to work
    else return 0;  //you may switch pops
}

void Controller::updatePop(){
    int maxpop = this->currentAttributes.food / 2;
    float popDelta = (maxpop - pop) * 0.1;
    if(popDelta > 1)
        popDelta = 1;
    else if(popDelta < -1)
        popDelta = -1;
    this->pop += popDelta;
}
//若还不能扩地则返回-1
int Controller::checkBorderUpdate(int &newX, int &newY){
    // todo: check whether the border should update or not, and if so, return the new culture threshold and expansion coordinates (newX, newY)
    if(world->getGrid()[newX][newY].Pop == WILD||currentAttributes.cul >= BorderExpandThreshold)//判断文化以及地块目前状态
    {
        Cell** adjacents = getAdjacentCells(newX, newY);//判断是否相邻
        bool flag = 0;
        for(int t = 0; t < 4; t++){
            if(adjacents[t] != 0){
                if(adjacents[t]->Pop != WILD)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            return BorderExpandThreshold * 2;
    }
    newX = -1;
    return 0;
}
//isAdding1为放置人口，0为移除，返回-1则为错误
int Controller::setPopAt(int m, int n, bool isAdding){
    // todo: add or remove the worker at (m, n), return 0 if the action is successful
    if(isAdding)
    {
        if(world->getGrid()[m][n].Pop == WILD||world->getGrid()[m][n].Pop == COLONIZED)
        {
            return -1;
        }
        world->getGrid()[m][n].Pop = COLONIZED;
        workingPop+=1;
    }
    else
    {
        if(world->getGrid()[m][n].Pop == WILD||world->getGrid()[m][n].Pop == OWNED)
        {
            return -1;
        }
        world->getGrid()[m][n].Pop = OWNED;
        workingPop-=1;
    }
}
//更新当前的各项属性，每次属性改变都要调用一次
void Controller::updateAttributes(){
    // todo: calculate and update the attributes according to the buffs
    currentAttributes.cul = 0;
    currentAttributes.food = 0;
    currentAttributes.prod = 0;
    currentAttributes.tech = 0;
    //建筑加成
    //人口加成
    Cell** grid = this->world->getGrid();
    int cur = 0;
    for(int i = 0; i < world->getGridHeight(); i++){
        for(int j = 0; j < world->getGridWidth(); j++){
            if(grid[i][j].buildingType!=NULL&&grid[i][j].buildingType->name == "won")
            {
                currentAttributes = currentAttributes + grid[i][j].buildingType->basicBonus;
            }
            else if(grid[i][j].Pop == COLONIZED){
                if(grid[i][j].buildingType != 0 && grid[i][j].prodAccumulated == 0)
                {
                    currentAttributes = currentAttributes + grid[i][j].buildingType->basicBonus;
                    currentAttributes = currentAttributes + grid[i][j].buildingType->popBonus * pop;
                }
                else if(grid[i][j].buildingType == 0)
                {
                    currentAttributes.food += landformBuffs[grid[i][j].landform][0];
                    currentAttributes.prod += landformBuffs[grid[i][j].landform][1];
                    int k = 0;
                    int nn = 0;
                    Cell** adjacents = getAdjacentCells(i, j);
                    while(grid[i][j].buildingType->locationBonusTargetBuildings[k] != '\0')
                    {
                        nn = getAdjacentSatisfied(adjacents,grid[i][j].buildingType->locationBonusTargetBuildings[k],grid[i][j].buildingType->locationBonusTargetLandform);
                        currentAttributes = currentAttributes + grid[i][j].buildingType->locationBonus * nn;
                        k++;
                    }
                }


            }

        }

    }
    //项目加成
    for(int i=0;i<activitySize;i++)
    {
        if(availableActivities[i]->remainingEffectedRounds)
        currentAttributes = currentAttributes + availableActivities[i]->basicBonus;
    }
    //availableActivities
}
//返回相邻地块指针数组
Cell** Controller::getAdjacentCells(int m, int n){
    // todo: get the adjacent cells from cell (m, n)
    Cell* adjacents[4];
    if(m!=0)
        adjacents[0]=&(world->getGrid()[m-1][n]);
    else
        adjacents[0]=0;
    if(n!=0)
        adjacents[1]=&(world->getGrid()[m][n-1]);
    else
        adjacents[1]=0;
    if(m!=world->getGridWidth())
        adjacents[2]=&(world->getGrid()[m+1][n]);
    else
        adjacents[2]=0;
    if(m!=world->getGridHeight())
        adjacents[3]=&(world->getGrid()[m][n+1]);
    else
        adjacents[3]=0;
    return adjacents;
}
//读取相邻加成按1计算,buildingname读取本方块中建筑的locationBonusTargetBuildings中每一个字符，即a，w；landformtype读取locationBonusTargetLandform
int Controller::getAdjacentSatisfied(Cell** adjacents, char buildingName, Landform landformType){
    // todo: check whether the adjacent cells satisfy the landformType and buildingName(s), you need to rewrite it if you use a hexagonal map
    unsigned satisfiedCellsNum = 0;
    for(int t = 0; t < 4; t++){
        if(adjacents[t] != 0){
            satisfiedCellsNum += ((adjacents[t]->buildingType && (buildingName == 'a' || adjacents[t]->buildingType->name[0] == buildingName))
                                  && adjacents[t]->landform == landformType);
        }
    }
    return satisfiedCellsNum;
}

