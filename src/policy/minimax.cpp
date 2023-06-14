#include <cstdlib>
//#include <fstream>
#include <unistd.h>

#include "../state/state.hpp"
#include "./Minimax.hpp"

int max(int a, int b){
    if(a > b) return a;
    return b;
}
int min(int a, int b){
    if(a < b) return a;
    return b;
}

int minimax(State *state, int depth, bool max_player){
    if(!depth) return state->evaluate();
    int value;
    auto actions = state->legal_actions;
    if(max_player){
        value = -2e9;
        for(int i = 0;i < actions.size();i++){
            value = max(value,minimax(state->next_state(actions[i]),depth-1,false));
        }
    }else{
        value = 2e9;
        for(int i = 0;i < actions.size();i++){
            value = min(value,minimax(state->next_state(actions[i]),depth-1,true));
        }
    }
    return value;
}

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  //sleep(1);
  //std::ofstream log("gamelog_.txt",std::ofstream::app);
  //log << state->evaluate() << "\n";
  
  int value = -2e9,ret;
  int select = 0;
  for(int i = 0;i < actions.size();i++){
    ret = minimax(state->next_state(actions[i]),depth,false);
    if(ret > value){
        select = i;
        value = ret;
    }
  }

  return actions[select];
}