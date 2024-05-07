#include "Game.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

Game::Game() : bird(0, 0), score(0), game_over(false) {  // Temporary initialization for bird
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, row, col);  // Get dimensions
    bird = Bird(col, row);       // Properly initialize bird with correct dimensions
    pipeCols.push_back(col);
    pipeHeights.push_back(rand() % (row - PIPE_GAP));
}

Game::~Game() {
    endwin();
}

void Game::drawBird() const {
    mvaddch(bird.y, bird.x, '@');
}

void Game::drawPipes() const {
    for (size_t i = 0; i < pipeCols.size(); i++) {
        for (int j = 0; j < row; j++) {
            if (j < pipeHeights[i] || j > pipeHeights[i] + PIPE_GAP) {
                mvaddch(j, pipeCols[i], '#');
            }
        }
    }
}

void Game::updatePipes() {
    for (auto& col : pipeCols) {
        col -= 2;
    }
    if (!pipeCols.empty() && pipeCols.front() < 0) {
        pipeCols.erase(pipeCols.begin());
        pipeHeights.erase(pipeHeights.begin());
    }
    if (pipeCols.empty() || col - pipeCols.back() > PIPE_FREQUENCY) {
        pipeCols.push_back(col);
        pipeHeights.push_back(rand() % (row - PIPE_GAP));
    }
}

bool Game::checkCollision() {
    for (size_t i = 0; i < pipeCols.size(); i++) {
        if (bird.x == pipeCols[i] &&
            (bird.y < pipeHeights[i] || bird.y > pipeHeights[i] + PIPE_GAP)) {
            return true;
        }
    }
    return false;
}

void Game::run() {
    while (!game_over) {
        clear();
        drawBird();
        drawPipes();
        timeout(100);
        int ch = getch();
        if (ch == 'q')
            break;
        if (ch == ' ')
            bird.flap();

        bird.applyGravity();
        updatePipes();

        if (checkCollision() || bird.y < 0 || bird.y >= row)
            game_over = true;

        mvprintw(0, 0, "Score: %d", score++);
        refresh();
        usleep(50000);
    }
}
