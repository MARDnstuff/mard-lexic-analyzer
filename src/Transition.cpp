#include "Transition.h"


void Transition::setTransition(char symbol, int sourceId, int targetId) {
    lowerSymbol = symbol;
    upperSymbol = symbol;
    sourceStateId = sourceId;
    targetStateId = targetId;
    return;
}

void Transition::setTransition(char lowSymbol, char upSymbol, int sourceId, int targetId) {
    lowerSymbol = lowSymbol;
    upperSymbol = upSymbol;
    sourceStateId = sourceId;
    targetStateId = targetId;
    return;
}

char Transition::getLowerSymbol() {
    return lowerSymbol;
}


void Transition::setLowerSymbol(char symbol) {
    lowerSymbol = symbol;
    return;
}


char Transition::getUpperSymbol() {
    return upperSymbol;
}


void Transition::setUpperSymbol(char symbol) {
    upperSymbol = symbol;
    return;
}

int Transition::getTransitionState(char symbol) {
    if(lowerSymbol <= symbol && symbol <= upperSymbol){
        return targetStateId;
    }
    return -1;
}

void Transition::setSourceStateId(int sourceId) {
    sourceStateId = sourceId;
    return;
}

int Transition::getSourceStateId() {
    return sourceStateId;
}

void Transition::setTargetStateId(int targetId) {
    targetStateId = targetId;
    return;
}

int Transition::getTargetStateId() {
    return targetStateId;
}

Transition::~Transition(){
    //dtor
}
