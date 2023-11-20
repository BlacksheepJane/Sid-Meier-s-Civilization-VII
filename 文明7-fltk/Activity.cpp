#include "Activity.h"
#include "Controller.h"

Activity::Activity(char* name, float prodSpent, Attributes basicBonus){
        this->name = name;
        this->prodSpent = prodSpent;
        this->basicBonus = basicBonus;     
    }

Activity::~Activity()
{
    //dtor
}
