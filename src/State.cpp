#include "State.h"
#include <vector>

State::State() {
    acceptanceState = false;
    token = -1;
    stateId = idStateCounter++;
    transitions.clear();
}

int State::getStateId() {
    return stateId;
}

void State::setStateId(int id) {
    stateId = id;
    return;
}

bool State::isAcceptanceState() {
    return acceptanceState;
}

void State::setAcceptanceState(bool value) {
    acceptanceState = value;
    return;
}

int State::getToken (){
    return token;
}

void State::setToken(int value){
    token = value;
    return;
}

void State::addTransition (Transition value){
    transitions.push_back(value);
}

State::~State(){
    //dtor
}
