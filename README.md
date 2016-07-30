# Game Of Life (2016)

This project is a PoC to see how GPUs are useful in this kind of problem.

The game of life is the best-known two-dimensional cellular automaton, invented by John H. Conway and popularized in Martin Gardner's Scientific American column starting in October 1970. The game of life was originally played (i.e., successive generations were produced) by hand with counters, but implementation on a computer greatly increased the ease of exploring patterns.

The life cellular automaton is run by placing a number of filled cells on a two-dimensional grid. Each generation then switches cells on or off depending on the state of the cells that surround it. The rules are defined as follows. All eight of the cells surrounding the current one are checked to see if they are on or not. Any cells that are on are counted, and this count is then used to determine what will happen to the current cell.

1. Death: if the count is less than 2 or greater than 3, the current cell is switched off.
2. Survival: if (a) the count is exactly 2, or (b) the count is exactly 3 and the current cell is on, the current cell is left unchanged.
3. Birth: if the current cell is off and the count is exactly 3, the current cell is switched on.

The game of life is a totalistic cellular automaton, and can be implemented as follows using the built-in command CellularAutomaton, where the initial conditions are specified as a binary matrix m and the results for generations g_1 through g_2 are returned. (Here, g=0 corresponds to the initial pattern.)

<br>
Technologies:
- OpenCL
- Maybe Vulkan or OpenGL or SDL
