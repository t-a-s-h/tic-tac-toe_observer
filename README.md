# Tic-Tac-Toe

A simple command line game of tic-tac-toe.
## Tech
C++.
## Run
### Option 1
- View demo [here](https://onlinegdb.com/Dwe7fH6xe)
### Option 2
- Download [here](https://github.com/t-a-s-h/tic-tac-toe_observer/archive/refs/heads/main.zip).
- Unzip folder.
- Navigate to unzipped folder in terminal.
- Run `make`.
- Run `./main` to start game.
## Current status
 #complete #cli 
## Notes
- Made to showcase / implement observer design pattern.
- This game uses a command line interface and can be played with one terminal instance only.
## Lessons
- Use of observer design pattern is unneeded here because squares do not need to "communicate" to each other. Squares only update the board which could have been accomplished in a more straightforward way.
- Use of Observer pattern tends to obfuscate the code, though it did make it slightly more reusable but still with the same issues (see Connect-4 game).
## Future considerations
- None.
