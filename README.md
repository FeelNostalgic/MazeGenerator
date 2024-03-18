# Maze Generator

Solved using DFS recursive to generate maze and DFS stack to generate path. 
## Solution to this interview problem

Create a two-dimensional random maze generator of size 'n' (n: odd > 3). The starting point A will always be in the top left corner. The end point B should be at the end of the longest path within your generated maze (not necessarily the top right corner). The maze should only have horizontal and vertical paths, not diagonal ones.

Also to get from A to B there should be only one possible path. 

### Example
n = 11 (* = wall, A = start, B = end).

![image](https://github.com/FeelNostalgic/MazeGenerator/assets/62141854/22ed3ef5-ebad-4f37-84ac-c65fdde60d45)


Implement the function: createMaze2D( n ) 
Do not generate just any maze, remember that you are asking for a maze with only one possible path between A and B.
Do not consider solutions that generate mazes with multiple paths between A and B.
