#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

using namespace std;

class Tetris {
  static const uint32_t lines   {20};
  static const uint32_t cols    {10};
  static const uint32_t squares {4};
  static const uint32_t shapes  {7};

  vector<vector<uint32_t>> area;
  vector<vector<uint32_t>> forms;

  struct Coords {
    uint32_t x, y;
  } z[squares], k[squares];

  shared_ptr<sf::RenderWindow> window;
  sf::Texture tiles, bg;
  shared_ptr<sf::Sprite> sprite, background;
  sf::Clock clock;
  sf::Font font;
  sf::Text txtScore, txtGameOver, txtBest;

  int dirx, color, score, bestScore;
  bool rotate, gameover;
  float timercount, delay;
  string filename;

  void saveScore();
  void loadBestScore();

protected:
  void events();
  void draw();
  void moveToDown();
  void setRotate();
  void resetValues();
  void changePosition();
  bool maxLimit();
  void setScore();

public:
  Tetris();
  void run();
};
