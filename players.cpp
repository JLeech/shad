#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm> 

using std::vector;

class Player {
  uint32_t effectiveness;
  uint32_t position;

  public:
  Player  (uint32_t effectiv, uint32_t pos) {
    effectiveness = effectiv;
    position = pos;
  }

  uint32_t getEffectiveness () const {
    return effectiveness;
  }

  uint32_t getPosition () const {
    return position;
  }
};

bool compare (Player fir, Player sec) {
  return fir.getEffectiveness () < sec.getEffectiveness ();
}

bool comparePositions (Player fir, Player sec) {
  return fir.getPosition () < sec.getPosition ();
}

std::vector<Player> recombination (std::vector<Player> command, Player currentPlayer) {
  
  int numberToDelete = 0;
  uint32_t headSum = 0;
  int size = command.size ();

  for ( int iter = 0; iter < size-1; ++iter ) {
    headSum += command[iter].getEffectiveness ();
    numberToDelete += 1;
    if  (iter == size - 2) {
      uint32_t part_sum = command[iter].getEffectiveness () + command[iter+1].getEffectiveness ();
      if  (part_sum > currentPlayer.getEffectiveness ()) {
        command.push_back (currentPlayer);
        break;
      } else {
        command.clear ();
        command.push_back (command[iter+1]);
        command.push_back (currentPlayer);
        break;
      }
    }
    uint32_t part_sum = command[iter+1].getEffectiveness () + command[iter+2].getEffectiveness ();
    if (part_sum > currentPlayer.getEffectiveness ()) {
      if (headSum > currentPlayer.getEffectiveness ()) {
        break;
      } else {
        command.erase (command.begin (), command.begin ()+numberToDelete);
        command.push_back (currentPlayer);
        break;
      }
    }
  }
  
  return command;
}

void makeCommand (std::vector<Player> players ) {
  
  std::vector<Player> command;
  uint32_t min_sum;
  for (int iter = 0; iter< players.size (); ++iter) {
    if  (command.size () < 2) {
      command.push_back (players[iter]);
    } else {
      min_sum = command[0].getEffectiveness () + command[1].getEffectiveness ();
      if (min_sum >= players[iter].getEffectiveness ()) {
        command.push_back (players[iter]);
      } else {
        command = recombination (command, players[iter]);
      }
    }
  }

  uint32_t out_sum = 0;
  
  for ( auto &i : command )  {
    out_sum += i.getEffectiveness();
  }
  std::cout << out_sum << "\n";
  
  std::sort (command.begin (), command.end (), comparePositions);

  for ( auto &i : command )  {
    std::cout << i.getPosition () + 1 << " ";
  }
}

std::vector <Player> ReadPlayers () {
  
  uint32_t playersCount;
  std::cin >> playersCount;
  std::vector<Player> players;
  for  (int i = 0; i < playersCount; ++i) {
    uint32_t effectiveness;
    std::cin >> effectiveness;
    players.push_back (Player (effectiveness, i));
  }

  return players;
}

std::vector<Player> readPlayers ()  {
  uint32_t numberPlayers;
  std::cin >> numberPlayers;
  std::vector<Player> players;
  for  (int i = 0; i < numberPlayers; ++i)  {
    int32_t playerEffectiveness;
    std::cin >> playerEffectiveness;
    players.push_back (Player (playerEffectiveness, i));
  }
  return players;
}

int main  ()  {
   
  std::vector<Player> players;
  players = readPlayers ();

  std::sort (players.begin (), players.end (), compare);

  makeCommand (players);
  return 0;
}
