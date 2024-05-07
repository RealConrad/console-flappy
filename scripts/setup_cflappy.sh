#!/bin/bash

# Variables
REPO_URL="https://github.com/yourusername/ConsoleFlappy.git"
GAME_DIR="$HOME/ConsoleFlappy"

# Check if the directory already exists
if [ ! -d "$GAME_DIR" ]; then
    echo "Cloning ConsoleFlappy..."
    git clone $REPO_URL $GAME_DIR
else
    echo "Directory already exists. Pulling latest changes..."
    git -C $GAME_DIR pull
fi

# Change to game directory and build
cd $GAME_DIR
make

# Check if the build was successful
if [ ! -f "ConsoleFlappy" ]; then
    echo "Build failed. Please check the output for errors."
    exit 1
fi

# Determine the shell and profile file to use
if [[ "$SHELL" == */zsh ]]; then
    PROFILE="$HOME/.zshrc"
elif [[ "$SHELL" == */bash ]]; then
    PROFILE="$HOME/.bashrc"
    if [ ! -f "$PROFILE" ]; then
        PROFILE="$HOME/.bash_profile"
    fi
else
    echo "Unsupported shell. Please use bash or zsh."
    exit 1
fi

# Add alias to the shell profile if it doesn't already exist
if ! grep -q 'alias cflappy=' "$PROFILE"; then
    echo "alias cflappy='$GAME_DIR/ConsoleFlappy'" >> "$PROFILE"
    echo "Alias 'cflappy' created for $SHELL. You might need to restart the terminal or source your profile."
    echo "source $PROFILE"
else
    echo "Alias 'cflappy' already set up in $PROFILE."
fi

echo "Installation and setup complete! Type 'cflappy' to start playing ConsoleFlappy."
