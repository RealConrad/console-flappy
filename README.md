# ConsoleFlappy
ConsoleFlappy is a simple, terminal-based clone of the popular game Flappy Bird, written in C++. The game is designed to run in UNIX-like terminal environments, including Linux and macOS. Players control a bird, attempting to navigate it through a series of obstacles without colliding.

## Features
- Simple terminal graphics using ncurses.
- Compatible with both Linux and macOS.
- Has a gameover screen.
- Be able to restart the game without needing to recompile/re-run the program 

## Prerequisites
Before installing and running ConsoleFlappy, ensure you have the following installed:
- A C++ compiler (g++ or clang)

## Installation
### Via Curl
Run the following command:
```bash
curl -o- https://raw.githubusercontent.com/RealConrad/ConsoleFlappy/main/scripts/setup_cflappy.sh | bash
```

The script executed above will add an alias for you. So just run:
```bash
cflappy
```

### Manually
Clone the repository:
```bash
git clone https://yourrepositorylink.com/ConsoleFlappy.git
cd ConsoleFlappy
```

Compile the program:
```bash
make
```
Run the game
```bash
./ConsoleFlappy
```

## Controls
- **Spacebar:** Make the bird flap
- **Q:** Quit the game

## License
MIT (see license tab)
