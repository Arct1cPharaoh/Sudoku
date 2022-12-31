#include <ctime>
#include <vector>
#include <iostream>
#include <cassert>

void print(const std::vector<std::vector<int>>& grid)
{ // Simple print function with ASCII art
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    for(unsigned int i = 0; i<grid.size(); i++)
    {
        std::cout << "+   |   |   +   |   |   +   |   |   +" << std::endl;
        for(unsigned int j = 0; j<grid[i].size(); j++)
        {
            if(j%3 == 0)
                std::cout << "+ ";
            else
                std::cout << "| ";
            if(grid[i][j] == 0)
                std::cout << "  ";
            else
            std::cout << grid[i][j] << " ";
            if(j== grid[i].size()-1)
            {
                std::cout << "+" << std::endl;
            }
        }
        std::cout << "+   |   |   +   |   |   +   |   |   +" << std::endl;
        if(i%3 == 2)
            std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
        else
            std::cout << "+-----------+-----------+-----------+" << std::endl;
    }
}

bool isValid(std::vector<std::vector<int>>& grid, int row, int col, int val)
{ // See if the input is a valid input
    for(unsigned int i = 0; i<9; i++)
    { // Checking the row
        if(grid[i][col] == val)
            return false;
    }
    for(unsigned int j = 0; j<9; j++)
    { // Checking the column
        if(grid[row][j] == val)
            return false;
    }
    int count1 = 0;
    int count2 = 0;
    for(int i = (row/3)*3; count1<3; i++)
    { // Checking the square
        count1++;
        for(int j = (col/3)*3; count2<3; j++)
        {
            count2++;
            if(grid[i][j] == val)
                return false;
        }
        count2=0;
    }
    // Wasnt found
    return true;
}

bool isFull(std::vector<std::vector<int>>& grid)
{ // Very simple function to check if the grid is full (used as the base case in recursion)
    for(unsigned int i = 0; i<9; i++)
    {
        for(unsigned int j = 0; j<9; j++)
        {
            if(grid[i][j] == 0)
                return false;
        }
    }
    return true;
}

int solve(std::vector<std::vector<int>>& grid, std::vector<std::vector<std::vector<int>>>& solutions)
{// The solving function (grid is the grid, solution is the current solution and solutions is the list of solutions)
    int ret = 0;
    if(isFull(grid))
    { // If it is a solution then push back the grid and return 1
        solutions.push_back(grid);
        return 1;
    }
    for(unsigned int i = 0; i<9; i++)
    {
        for(unsigned int j = 0; j<9; j++)
        {
            if(grid[i][j] == 0)
            {
                for(int k = 1; k<10; k++)
                {
                    if(isValid(grid, i, j, k))
                    { // Goes through every spot until the first, goes through every digit to see if it is valid and runs solve on the new grid (reverting the grid after)
                        grid[i][j] = k;
                        ret += solve(grid, solutions);
                        grid[i][j] = 0;
                    }
                }
                i=9;
                j=9;
            }
        }
    }
    return ret;
}

int checkChanges(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& correct)
{ // Function to figure out how many differences
    int count = 0;
    for(unsigned int i = 0; i<grid.size(); i++)
    {
        for(unsigned int j = 0; j<grid[i].size(); j++)
        {
            if(grid[i][j] != correct[i][j])
                count++;
        }
    }
    return count;
}

bool recursiveGenerator(std::vector<std::vector<int>>& puzzle)
{
    srand(time(NULL));
    if(isFull(puzzle))
    { // Base case
        return true;
    }

    for(int i = 0; i<9; i++)
    {
        for(int j = 0; j<9; j++)
        {
            if(puzzle[i][j] == 0)
            { // Found next empty spot
                int back = 1+rand()%9;
                for(int k = back; k<10; k++)
                {
                    if(isValid(puzzle, i, j, k))
                    {
                        puzzle[i][j] = k;
                        if(recursiveGenerator(puzzle))
                            return true;
                        puzzle[i][j]=0;
                    }
                }

                for(int k = back; k>0; k--)
                {
                    if(isValid(puzzle, i, j, k))
                    {
                        puzzle[i][j] = k;
                        if(recursiveGenerator(puzzle))
                            return true;
                        puzzle[i][j]=0;
                    }
                }
                return false;
                // Dont repeat over and over again
                i=10;
                j=10;
            }
        }
    }
    return false;
}

void generatePuzzle(std::vector<std::vector<int>>& puzzle, std::vector<std::vector<int>>& show)
{
    std::vector<std::vector<int>> revert = puzzle;
    while(true)
    {
        srand(time(NULL));
        puzzle = revert;
        int functional = true;
        for(int i = 0; i<9; i++)
        {
            for(int j = 0; j<9; j++)
            {
                bool found = false;
                int back = 1+rand()%9;
                for(int k = back; k<10; k++)
                {
                    if(isValid(puzzle, i, j, k))
                    {
                        found = true;
                        puzzle[i][j] = k;
                        print(puzzle);
                        k=10;
                    }
                }
                if(!found)
                {
                    for(int k = back; k>0; k--)
                    {
                        if(isValid(puzzle, i, j, k))
                        {
                            found = true;
                            puzzle[i][j] = k;
                            print(puzzle);
                            k=0;
                        }
                    }
                }
                if(!found)
                { // No valid puzzle for this combination
                    std::cout << "BAD PUZZLE" << std::endl;
                    functional = false;
                    i = 10;
                    j = 10;
                }
            }
        }
        if(functional)
            break;
    }
    //print(puzzle);
    show=puzzle;
    int numFilled = 81;
    int changeX, changeY;
    std::vector<std::vector<std::vector<int>>> solutions;
    while(true) {
        while(solve(show, solutions) == 1)
        {
            changeX = rand()%10;
            changeY = rand()%10;
            if(show[changeX][changeY] != 0)
            {
                numFilled--;
                show[changeX][changeY] = 0;
            }
            std::cout << "Changing Solution" << std::endl;
        }
        show[changeX][changeY] = puzzle[changeX][changeY];
        if(numFilled <= 41)
            return;
    }
}

// Finds the last board with one solution
std::vector<std::vector<int>>
findBoard(std::vector<std::vector<int>>& answer)
{
    std::vector<std::vector<int>> puzzle;
    for(int i = 0; i<10; i++)
    {
        std::vector<int> a(9, 0);
        puzzle.push_back(a);
    }
    recursiveGenerator(puzzle);

    srand (time(NULL)); // Set seed

	std::vector<std::vector<std::vector<int>>> useless;
	std::vector<std::vector<int>> preveousPuzzle = puzzle;
	while (solve(puzzle, useless) <  2) 
	{
		preveousPuzzle = puzzle;
		int randX = rand()%9;
		int randY = rand()%9;
		puzzle[randX][randY] = 0;
	}
    assert(solve(preveousPuzzle, useless) == 1);
    //answer = puzzle;
	return preveousPuzzle;
}


