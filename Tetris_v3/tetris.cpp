#include "tetris.hpp"
#include <fstream>

Tetris::Tetris() {
  area.resize(lines);
  for (size_t i {}; i < area.size(); ++i) {
    area[i].resize(cols);
  }

  forms = {
    {1,3,5,7}, // I
    {2,4,5,7}, // Z
    {3,5,4,6}, // S
    {3,5,4,7}, // T
    {2,3,5,7}, // L
    {3,5,7,6}, // J
    {2,3,4,5}, // O
  };

  window = make_shared<sf::RenderWindow>(
      sf::VideoMode(360, 720),
      "GRA TETRIS ",
      sf::Style::Titlebar | sf::Style::Close
      );
  window->setPosition(sf::Vector2i(100, 100));

  tiles.loadFromFile("./resources/img/squares.png");
  sprite = make_shared<sf::Sprite>();
  sprite->setTexture(tiles);
  sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));

  bg.loadFromFile("./resources/img/background.png");
  background = make_shared<sf::Sprite>();
  background->setTexture(bg);

  dirx = score = {0};
  rotate = gameover = {false};
  timercount = {0.f};
  delay = {0.3f};
  color = {1};

  uint32_t number = rand() % shapes;
  for (size_t i {}; i < squares; ++i) {
    z[i].x = forms[number][i] % 2;
    z[i].y = forms[number][i] / 2;
  }

  font.loadFromFile("./resources/font/font.ttf");
  txtScore.setFont(font);
  txtScore.setPosition(100.f, 10.f);
  txtScore.setString("WYNIK: " + to_string(score));
  txtScore.setCharacterSize(30);
  txtScore.setOutlineThickness(3);

  txtBest.setFont(font);
  txtBest.setPosition(10.f, 650.f);
  txtBest.setString("NAJLEPSZY WYNIK: ");
  txtBest.setCharacterSize(20);
  txtBest.setOutlineThickness(3);

  txtGameOver.setFont(font);
  txtGameOver.setPosition(30.f, 300.f);
  txtGameOver.setString("GAME OVER");
  txtGameOver.setCharacterSize(50);
  txtGameOver.setOutlineThickness(3);

  filename = "scores.txt";
  loadBestScore();
}

void Tetris::saveScore() {
  ofstream file(filename);
  if (file.is_open()) {
    file << bestScore;
    file.close();
  }
}

void Tetris::loadBestScore() {
  ifstream file(filename);
  if (file.is_open()) {
    file >> bestScore;
    file.close();
  }
}

void Tetris::events() {
  float time = clock.getElapsedTime().asSeconds();
  clock.restart();
  timercount += time;

  auto e = make_shared<sf::Event>();
  while (window->pollEvent(*e)) {
    if (e->type == sf::Event::Closed) {
      window->close();
    }

    if (e->type == sf::Event::KeyPressed) {
      if (e->key.code == sf::Keyboard::Up) {
        rotate = true;
      }
      else if (e->key.code == sf::Keyboard::Right) {
        ++dirx;
      }
      else if (e->key.code == sf::Keyboard::Left) {
        --dirx;
      }
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    delay = 0.05f;
  }
}

void Tetris::draw() {
  window->clear(sf::Color::Black);
  window->draw(*background);

  for (size_t i {}; i < lines; ++i) {
    for (size_t j {}; j < cols; ++j) {
      if (area[i][j] != 0) {
        sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36));
        sprite->setPosition(j * 36, i * 36);
        window->draw(*sprite);
      }
    }
  }

  for (size_t i {}; i < squares; ++i) {
    sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36));
    sprite->setPosition(z[i].x * 36, z[i].y * 36);
    window->draw(*sprite);
  }

  window->draw(txtScore);
  window->draw(txtBest);
  if (gameover) {
    window->draw(txtGameOver);
  }
  window->display();
}

void Tetris::run() {
  while (window->isOpen()) {
    events();
    if (!gameover) {
      changePosition();
      setRotate();
      moveToDown();
      setScore();
      resetValues();
    }
    draw();
  }
}

void Tetris::moveToDown() {
  if (timercount > delay) {
    for (size_t i {}; i < squares; ++i) {
      k[i] = z[i];
      ++z[i].y;
    }

    if (maxLimit()) {
      for (size_t i {}; i < squares; ++i) {
        area[k[i].y][k[i].x] = color;
      }

      color = rand() % shapes + 1;
      uint32_t number = rand() % shapes;
      for (size_t i {}; i < squares; ++i) {
        z[i].x = forms[number][i] % 2;
        z[i].y = forms[number][i] / 2;
      }
    }

    timercount = 0;
  }
}

void Tetris::setRotate() {
  if (rotate) {
    Coords coords = z[1];
    for (size_t i {}; i < squares; ++i) {
      int x = z[i].y - coords.y;
      int y = z[i].x - coords.x;

      z[i].x = coords.x - x;
      z[i].y = coords.y + y;
    }

    if (maxLimit()) {
      for (size_t i {}; i < squares; ++i) {
        z[i] = k[i];
      }
    }
  }
}

void Tetris::resetValues() {
  dirx = 0;
  rotate = false;
  delay = 0.3f;
}

void Tetris::changePosition() {
  for (size_t i {}; i < squares; ++i) {
    k[i] = z[i];
    z[i].x += dirx;
  }

  if (maxLimit()) {
    for (size_t i {}; i < squares; ++i) {
      z[i] = k[i];
    }
  }
}

bool Tetris::maxLimit() {
  for (size_t i {}; i < squares; ++i) {
    if (z[i].x < 0 || z[i].x >= cols || z[i].y >= lines) {
      return true;
    }
    if (area[z[i].y][z[i].x] != 0) {
      return true;
    }
  }

  return false;
}

void Tetris::setScore() {
  int count {};
  for (size_t i {}; i < lines; ++i) {
    for (size_t j {}; j < cols; ++j) {
      if (area[i][j] != 0) {
        ++count;
      }
      area[i][j] = 0;
    }
    if (count == cols) {
      for (size_t k {i}; k > 0; --k) {
        for (size_t j {}; j < cols; ++j) {
          area[k][j] = area[k - 1][j];
        }
      }
      ++score;
    }
    count = 0;
  }

  txtScore.setString("WYNIK: " + to_string(score));

  if (score > bestScore) {
    bestScore = score;
    saveScore();
  }

  txtBest.setString("NAJLEPSZY WYNIK: " + to_string(bestScore));
}

