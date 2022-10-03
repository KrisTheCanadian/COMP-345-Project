#include "GameEngine.h"

void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
}

GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

GameEngine::GameEngine(GameEngineState state) {
  this->state = state;
}

GameEngine::GameEngine() {
  this->state = GameEngineState::GE_Start;
}

std::string GameEngine::getCurrentStateToString() {
  switch (this->state) {
    case GE_Start:
      return "Start";
    case GE_Map_Loaded:
      return "Map Loaded";
    case GE_Map_Validated:
      return "Map Validated";
    case GE_Players_Added:
      return "Players Added";
    case GE_Reinforcement:
      return "Assign Reinforcement";
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
    case GE_Win:
      return "Win";
  }
}
