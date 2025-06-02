# Minesweeper

A modern C++/SFML version of the classic Minesweeper game, featuring custom board sizes, player name input, a digital timer, leaderboard, and more.

---

## Features

- **Graphical User Interface**: Built with SFML for smooth visuals and interaction.
- **Configurable Board**: Reads board size and mine count from `config.cfg`.
- **Player Name Input**: Enter your name before starting; used for leaderboard entries.
- **Pause/Resume**: Pause and resume gameplay at any time.
- **Restart**: Instantly restart the game with the same configuration.
- **Debug Mode**: Toggle to reveal all mines for testing or learning.
- **Leaderboard**: View the fastest completion times and player names.
- **Digital Timer & Counter**: Track elapsed time and remaining mines/flags.
- **Win/Loss Feedback**: Animated face icons for win, loss, and in-game states.
- **Modular Code**: Organized into `Tile`, `Board`, and supporting classes for clarity and extensibility.

---

## How to Build

### Dependencies:

- C++17 or newer  
- SFML 2.5+

### Clone the repository:

```bash
git clone https://github.com/yourusername/minesweeper.git
cd minesweeper
```

### Build (example using g++):

```bash
g++ -std=c++17 Main.cpp Board.cpp TextureManager.cpp -lsfml-graphics -lsfml-window -lsfml-system -o minesweeper
```

> Adjust source files and library flags as needed.

### Run:

```bash
./minesweeper
```

---

## Gameplay Instructions

- **Start**: Enter your name on the welcome screen and press Enter.
- **Left Click**: Reveal a tile.
- **Right Click**: Flag/unflag a tile as a mine.
- **Pause/Play**: Use the pause/play button to stop/resume the timer and gameplay.
- **Restart**: Click the face icon to restart the current board.
- **Debug**: Toggle debug mode to show all mines (for practice/testing).
- **Leaderboard**: View top scores by clicking the leaderboard button.

---

## File Structure

| File               | Purpose                                       |
|--------------------|-----------------------------------------------|
| `Main.cpp`         | Entry point, handles UI and main game loop    |
| `Board.cpp/h`      | Board logic, mine placement, tile management  |
| `Tile.h`           | Tile structure and state                      |
| `TextureManager.*` | Manages textures and sprites                  |
| `config.cfg`       | Board configuration (columns, rows, mines)    |
| `leaderboard.txt`  | Stores leaderboard data                       |
| `assets/`          | Contains textures, fonts, and icons           |

---

## Configuration

Edit `config.cfg` to set board dimensions and mine count:

```
columns
rows
mines
```

**Example:**
```
16
16
40
```

---

## Leaderboard

Fastest times and player names are saved to `leaderboard.txt`.

View via the leaderboard button in-game.

---

## Credits

- Developed by **Jacs**
- Uses **SFML** for graphics and window management

---

## License

MIT License. See `LICENSE` for details.

---

Have fun playing **Minesweeper**!
