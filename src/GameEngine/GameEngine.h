#pragma once
#include <string>

enum GameEngineState {
  GE_Start = 0,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Issue_Orders,
  GE_Execute_Orders,
  GE_Win
};

class GameEngine {
private:
  GameEngineState state = GE_Start;

public:
  GameEngine();
  explicit GameEngine(GameEngineState state);
  GameEngineState getCurrentState();
  void setCurrentState(GameEngineState engineState);
  std::string getCurrentStateToString();
};