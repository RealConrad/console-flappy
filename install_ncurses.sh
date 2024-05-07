#!/bin/bash

# Function to check if ncurses is installed
is_ncurses_installed() {
	# Attempt to compile a small test program including ncurses.h
	echo -e "#include <ncurses.h>\nint main() { initscr(); endwin(); return 0; }" | gcc -x c - -lncurses -o /dev/null 2>/dev/null
	return $?
}

# Check if ncurses is installed by trying to compile a small program that uses ncurses
if is_ncurses_installed; then
	echo "ncurses is already installed."
else
	echo "ncurses not found, installing..."
	# Determine OS and install ncurses if it's not installed
	if [[ "$OSTYPE" == "linux-gnu"* ]]; then
		# Using apt-get to install ncurses
		sudo apt-get update
		sudo apt-get install libncurses5-dev libncursesw5-dev
	elif [[ "$OSTYPE" == "darwin"* ]]; then
		# Check if Homebrew is installed and install it if not
		which brew > /dev/null || /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
		brew install ncurses
	else
		echo "Unsupported operating system."
		exit 1
	fi
fi
