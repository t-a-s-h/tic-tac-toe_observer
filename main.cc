#include "tic-tac-toe.h"

using namespace std;

int main() {
  Grid g;
  while(!g.isGameOver()) {
    g.setSquare();
    cout << g;
  }
  cout << (!g.getXTurn() ? 'X' : 'O') << " WINS!" << endl;
}