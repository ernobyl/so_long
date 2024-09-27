# so_long
A basic 2d game with collectibles and an exit.
## Running the game
- The game's graphical interface utilizes the [MLX42 library](https://github.com/codam-coding-college/MLX42) which itself is dependent on [GLFW](https://github.com/glfw/glfw).

- Once the game along with the MLX42 library is compiled. Run the game with ./so_long maps/mapname.ber

## About the game
### Map parsing
- A map must have the .ber suffix to be valid
- A map must consist of these elements:
    - Walls (1)
    - Floor (0)
    - The starting position of the player (P)
    - Collectibles (C)
    - An exit which opens once all collectibles are collected (E)
- The map must also have a valid path
- No blocked collectibles or blocked exit
- No duplicate exits or player starting positions
- Map's outer perimeter must be walled
### Keys
- Move using WASD
- Close window with esc
