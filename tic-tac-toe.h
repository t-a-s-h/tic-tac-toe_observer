#include <vector>
#include <array>
#include <cstddef>
#include <iostream>
#include <map>

enum class PathType { H, V, D };

enum class Mark { X, O, None };

class Grid;

class Display {
  const static size_t size = 3;
  std::array<std::array<char,size>,size> theDisplay;
  public:
    Display();
    void notify(Square* s);
    friend std::ostream& operator<<(std::ostream& out, Display* d);
};

class Path {
  PathType type;
  size_t n;
  size_t count;
  Mark mark;
  public:
  void incTypeCount();
  void resetCount();
  const Mark getMark() const;
  void setMark(Mark m);
  size_t getTypeCount();
  const PathType getType() const;
  const size_t getIndex() const;
  Path(PathType t, size_t n, size_t count = 0);
  friend bool operator<(const Path p, const Path o);
};

class Square {
  const static size_t size = 3;
  Mark type;
  Display* o;
  int row;
  int col;
  public:
    std::map<Path*,size_t> inPaths;
    Square(int x, int y);
    int getRow() const;
    int getCol() const;
    void notify(Grid* g);
    void attach(Display* o); // attach adjacent squares that could help form 3 in row on play
    void detach(); // detach if item in row can no longer help win
    void notifyObservers();
    const Mark getType() const;
    const bool getPlayed() const;
    const char getChar() const;
    void setType(bool isX);
    void setCoords(int x, int y);
    friend std::ostream& operator<<(std::ostream& o, Square s);
};

class Grid {
  static const size_t size = 3;
  std::array<std::array<Square*,size>,size> theGrid;
  bool xTurn;
  size_t num_played;
  std::map<Path*,size_t> pathList;
  Display* dp;
  bool gameOver;
  public: 
    size_t getCount(Path* p);
    const bool isDraw();
    const size_t incNumPlayed();
    void setGameOver();
    Grid();
    bool isGameOver();
    const bool getXTurn() const;
    void setXTurn(Square* s);
    void setSquare();
    friend std::ostream& operator<<(std::ostream& out, Grid g);
};

class Observer {
  protected:
  enum SubscriptionType { All, Inline };
  public:
    virtual void notify(Grid* g) = 0;
    virtual ~Observer() = default;
};