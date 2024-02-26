#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;

void createMaze2D(int n);

class Maze
{
public:
    vector<vector<char>> maze;
    vector<vector<int>> mazeWeigth;
    vector<vector<bool>> visited;
    pair<int, int> farthestCell;
    stack<pair<int, int>> visitedStack;
    int maxLength;
    int mazeSize;

    Maze(int n)
    {
        mazeSize = n;
        maze = vector<vector<char>>(n, vector<char>(n, '#'));
        mazeWeigth = vector<vector<int>>(n, vector<int>(n, 0));
        visited = vector<vector<bool>>(n, vector<bool>(n, false));
        maxLength = 0;
    }

    void printMaze()
    {
        for (const auto& row : maze)
        {
            for (auto cell : row)
            {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    void generateMaze()
    {
        srand(time(0));
        generateMazeRecursive(1, 1);
        maze[1][1] = 'A';
    }

    void generateMaxPath()
    {
        //findLongestPath(1, 1, 0);
        findLongestPathByStack(1, 1);
        maze[farthestCell.first][farthestCell.second] = 'B';
    }
    
private:
    void generateMazeRecursive(int x, int y)
    {
        maze[y][x] = ' ';

        // Directions = Up, Right, Left, Down
        int directions[4][2] = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};

        // Randomize directions
        for (auto& direction : directions)
        {
            int randomIndex = rand() % 4;
            swap(direction, directions[randomIndex]);
        }

        // Iterate for each random direction
        for (auto& direction : directions)
        {
            int newXPosition = x + direction[0];
            int newYPosition = y + direction[1];

            // Check if the new position is inside the maze and is still not visited
            if (newXPosition > 0 && newXPosition < maze[0].size() - 1 && newYPosition > 0 && newYPosition < maze.size() - 1 && maze[newYPosition][newXPosition] == '#')
            {
                maze[newYPosition][newXPosition] = ' ';
                int wallY = y + direction[1] / 2;
                int wallX = x + direction[0] / 2;
                maze[wallY][wallX] = ' '; // Delete wall(cell) between (x,y) and (newXPosition, newYPosition)
                generateMazeRecursive(newXPosition, newYPosition);
            }
        }
    }

    void findLongestPath(int x, int y, int length)
    {
        // Outside of maze bounds, wall or visited cell -> end recursion
        if (x <= 0 || x >= maze.size() || y <= 0 || y >= maze.size() || maze[x][y] == '#') return;
        if (visited[x][y])
        {
            if (length >= maxLength)
            {
                maxLength = length;
                farthestCell = make_pair(x, y);
            }
            return;
        }

        visited[x][y] = true; //Set current cell as visited

        // Look all directions
        findLongestPath(x + 1, y, length + 1); // Down
        findLongestPath(x - 1, y, length + 1); // Up
        findLongestPath(x, y + 1, length + 1); // Right
        findLongestPath(x, y - 1, length + 1); // Left

        visited[x][y] = false; // Set current cell as not visited
    }

    void findLongestPathByStack(int startX, int startY)
    {
        farthestCell = make_pair(startX, startY);
        visitedStack.push(farthestCell);
        int length = 0;
        mazeWeigth[startX][startY] = 0;
        
        while (!visitedStack.empty())
        {
            auto current = visitedStack.top();
            visitedStack.pop();
            int currentX = current.first;
            int currentY = current.second;
            //maze[farthestCell.first][farthestCell.second] = '.';
            //printMaze();

            visited[current.first][current.second] = true;

            //Down
            checkNeighbour(currentX + 1, currentY, currentX, currentY);
            // Up
            checkNeighbour(currentX - 1, currentY, currentX, currentY);
            // Right
            checkNeighbour(currentX, currentY + 1, currentX, currentY);
            // Left
            checkNeighbour(currentX, currentY - 1, currentX, currentY);
        }
    }

    void checkNeighbour(int x, int y, int& currentX, int& currentY)
    {
        if (x > mazeSize - 1 || x <= 0 || y > mazeSize - 1 || y <= 0 || maze[x][y] == '#' || visited[x][y]) return;

        visitedStack.push(make_pair(x, y));
        mazeWeigth[x][y] = mazeWeigth[currentX][currentY] + 1;
        if (mazeWeigth[x][y] > maxLength)
        {
            maxLength = mazeWeigth[x][y];
            farthestCell = make_pair(x, y);
        }
    }
};

int main(int argc, char* argv[])
{
    createMaze2D(11);

    return 0;
}

void createMaze2D(int n)
{
    Maze maze(n);
    maze.generateMaze();
    maze.generateMaxPath();
    maze.printMaze();
    cout << "Path length: " <<  maze.maxLength <<endl;
}
