#include "tic-tac-toe.h"

using namespace std;

Display::Display(){ for (auto& r : theDisplay) r.fill(' '); }

Grid::Grid():xTurn{true},dp{new Display},gameOver{false} {
  for (size_t i = 0; i < size; ++i) {
    pathList[new Path(PathType::H,i)] = 0;
    pathList[new Path(PathType::V,i)] = 0;
  }

  pathList[new Path(PathType::D,0)] = 0;
  pathList[new Path(PathType::D,1)] = 0;

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      Square* s = new Square(j,i);
      theGrid.at(j).at(i) = s;
      s->attach(dp);
    }
  }
  for (auto& [path, index] : pathList) {
    size_t first = 0;
    size_t second =  0;
    for (size_t i = 0; i < size; ++i) {
      if (path->getType() == PathType::H) {
        first = i;
        second =  path->getIndex();
      }
      else if (path->getType() == PathType::V) {
        first = path->getIndex();
        second =  i;
      }
      else if (path->getType() == PathType::D) {
        first = i;
        second = (path->getIndex() == 0 ? i : 2 - i);
      }
      theGrid.at(first).at(second)->inPaths[path] = 0;
    }
  }
}

void Grid::setGameOver() { gameOver = true; }

void Square::setCoords(int x, int y) { row = y; col = x; }

ostream& operator<<(ostream& o, Square s) { return o; }

Path::Path(PathType t, size_t n, size_t count):type{t},n{n},count{count},mark{Mark::None}{}

bool operator<(const Path p, const Path o) {
  return p.type < o.type || p.n < o.n;
}

size_t const Path::getIndex() const{ return n; }

size_t Grid::getCount(Path* p) { return pathList[p]; }

Square::Square(int x, int y):type{Mark::None},row{y},col{x}{}

const Mark Square::getType() const { return type; };

const bool Square::getPlayed() const { return type != Mark::None; };

void Square::setType(bool isX) { type = isX ? Mark::X : Mark::O; };

int Square::getRow() const { return row; }

int Square::getCol() const { return col; }

const char Square::getChar() const { 
  char c = ' ';
  switch (type) {
    case Mark::X:
      c = 'x';
      break;
    case Mark::O:
      c = 'o';
      break;
    default:
      break;
  }
  return c;
}

// notifies display
void Square::notifyObservers() { o->notify(this); }

void Path::incTypeCount() { ++count; }

void Path::resetCount() { mark = Mark::None; count = 0; }

const Mark Path::getMark() const { return mark; }

void Path::setMark(Mark m) { mark = m; }

const PathType Path::getType() const { return type; }

size_t Path::getTypeCount() { return count; }

void Square::notify(Grid* g) {
  if (getPlayed()) return;
  setType(g->getXTurn());
  for (auto& [path, n] : inPaths) {
    if (path->getMark() == Mark::None) {
      path->setMark(type);
      path->incTypeCount();
    } else if (path->getMark() == type) {
      path->incTypeCount();
    } else {
      path->resetCount();
    }
    if (path->getTypeCount() >= size) {
      g->setGameOver();
      cout << (g->isGameOver() ? "game over" : "game not over") << endl;
      return;
    }
  }
}

void Square::attach(Display* dp) { o = dp; }

void Square::detach() { o = nullptr; }

void Display::notify(Square* s) {
  theDisplay.at(s->getRow()).at(s->getCol()) = s->getChar();
}

ostream& operator<<(ostream& out, Display* d) {
  for (auto& r : d->theDisplay) {
    for (char c : r) {
      out << c;
    }
    out << endl;
  }
  return out;
}

const bool Grid::getXTurn() const { return xTurn; }

void Grid::setXTurn(Square* s) { xTurn = !xTurn; xTurn ? s->setType(false) : s->setType(true); }

void Grid::setSquare() {
  int x,y;
  cout << "Play" << ' ' << (getXTurn() ? 'X' : 'O') << endl;
  cin >> x >> y;
  Square* s = theGrid.at(y).at(x);
  while (s->getPlayed()) {
    cout << "Try again" << endl;
    cin >> x >> y;
    s = theGrid.at(y).at(x);
  }
  s->notify(this);
  setXTurn(s);
  s->notifyObservers();
}

ostream& operator<<(ostream& out, Grid g) { return out << g.dp; }

bool Grid::isGameOver() { return gameOver; }