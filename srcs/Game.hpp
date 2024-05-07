#ifndef GAME_HPP
#define GAME_HPP

#include "Bird.hpp"
#include <vector>

#define PIPE_GAP 5
#define PIPE_FREQUENCY 20  // Distance between pipes

class Game {
private:
    int row, col;
    Bird bird;
    std::vector<int> pipeCols;
    std::vector<int> pipeHeights;
    int score;
    bool game_over;

public:
    Game();
    ~Game();
    void run();

    void drawBird() const;
    void drawPipes() const;
    void updatePipes();
    bool checkCollision();
};

#endif // GAME_HPP
