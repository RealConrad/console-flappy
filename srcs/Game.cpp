#include "Game.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

Game::Game() : bird(0, 0), score(0), game_over(false) { // Temporary initialization for bird
	srand(time(NULL));
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, row, col); // Get terminal dimensions
	bird = Bird(col, row); // Properly initialize bird with correct dimensions
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
	int pipe_speed = 2; // Speed at which pipes move left

	// Move each pipe left by 'pipe_speed'
	for (size_t i = 0; i < pipeCols.size(); ++i) {
		pipeCols[i] -= pipe_speed;

		// Clearing the pipe position left behind
		if (pipeCols[i] + pipe_speed < col) {
			for (int j = 0; j < row; ++j) {
				if (j < pipeHeights[i] || j > pipeHeights[i] + PIPE_GAP) {
					mvaddch(j, pipeCols[i] + pipe_speed, ' '); // Clear old positions
				}
			}
		}
	}

	// Remove pipe if it moves off-screen
	if (!pipeCols.empty() && pipeCols.front() < 0) {
		pipeCols.erase(pipeCols.begin());
		pipeHeights.erase(pipeHeights.begin());
	}

	// Add new pipe when last pipe moves past a defined frequency
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

void Game::resetGame() {
	clear();  // Clear the entire screen before resetting game elements
	score = 0;
	game_over = false;
	bird = Bird(col, row);
	pipeCols.clear();
	pipeHeights.clear();
	pipeCols.push_back(col); // Start with one pipe on the right of the screen
	pipeHeights.push_back(rand() % (row - PIPE_GAP));
	refresh(); // Refresh the screen to show the cleared state
}

void Game::gameOver() {
	clear();
	mvprintw(row / 2, (col - 10) / 2, "GAME OVER!");
	mvprintw(row / 2 + 1, (col - 28) / 2, "Press 'q' to quit or 'r' to restart.");
	refresh();

	// Handle game over input
	while (true) {
		int ch = getch();
		if (ch == 'q') {
			break;
		} else if (ch == 'r') {
			resetGame();
			run();
			break;
		}
	}
}

void Game::startGame() {
	clear();
	mvprintw(row / 2, (col - 10) / 2, "PRESS SPACEBAR TO START!");
	while (true) {
		int ch = getch();
		if (ch == ' ')
			break;
	}
	clear();
}

void Game::run() {
	startGame();
	int prevBirdY = bird.y;  // Track the previous Y position of the bird for clearing

	while (!game_over) {
		timeout(0); // Non-blocking input to make the game feel more responsive
		int ch = getch();
		if (ch == 'q')
			return;
		if (ch == ' ')
			bird.flap();

		// Clear the previous positions
		mvaddch(prevBirdY, bird.x, ' ');
		for (size_t i = 0; i < pipeCols.size(); ++i) {
			if (pipeCols[i] + 1 < col) {  // Only clear if within screen bounds
				for (int j = 0; j < row; ++j) {
					if (j < pipeHeights[i] || j > pipeHeights[i] + PIPE_GAP) {
						mvaddch(j, pipeCols[i] + 1, ' ');  // Clear old pipe positions
					}
				}
			}
		}

		bird.applyGravity();
		updatePipes();

		drawBird(); // Draw the bird at the new position
		drawPipes(); // Draw pipes at new positions

		if (checkCollision() || bird.y < 0 || bird.y >= row) {
			game_over = true;
		} else {
			mvprintw(0, 0, "Score: %d", score++);
			refresh();
			usleep(100000); // games tick timer
		}
		
		prevBirdY = bird.y; // Update the bird's previous position for the next frame
	}
	gameOver();
}
