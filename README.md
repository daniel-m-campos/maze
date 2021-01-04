# Maze

A small implementation of the A* search algorithm for path finding to practice C++, CMake, and Catch2.

```bash
👋 Welcome to the Maze!
The current maze is:
🌌  👾️  🌌  🌌  🌌  🌌  
🌌  👾️  🌌  🌌  🌌  🌌  
🌌  👾️  🌌  🌌  🌌  🌌  
🌌  👾️  🌌  🌌  🌌  🌌  
🌌  🌌  🌌  🌌  👾️  🌌  
Continue with this maze? {Y|n} >> y
Please provide your start "x,y" without quotes >> 0,0
Please provide your goal "x,y" without quotes >> 4,5
🔎 Searching...  
🤖 Found a path!
🚦  👾️  🌌  🌌  🌌  🌌  
🚀  👾️  🌌  🌌  🌌  🌌  
🚀  👾️  🌌  🌌  🌌  🌌  
🚀  👾️  🌌  🚀  🚀  🚀  
🚀  🚀  🚀  🚀  👾️  🏁  
Until next time! 👍
```

## Installing
```bash
git clone git@github.com:daniel-m-campos/maze.git
cd maze
mkdir build
cd build
cmake ..
make
```

## Running
Once installed:
```bash
cd src # from build directory
./MAZE
```