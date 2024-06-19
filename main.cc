#include "tic-tac-toe.h"

using namespace std;

int main() {
  Grid g;
  while(!g.isGameOver()) {
    g.setSquare();
    cout << g;
  }
  if (!g.isDraw()) cout << (!g.getXTurn() ? 'X' : 'O') << " WINS!" << endl;
  else cout << "Draw." << endl;
}