#include "GameState.h"

using namespace ExomoSnake;

GameState::GameState()
{
    //ctor
}

GameState::~GameState()
{
    //dtor
}

StateMachine::StateMachine(const GameStatePtr& initialState)
    : currentState(initialState)
{

}
