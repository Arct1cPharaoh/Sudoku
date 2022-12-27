#include <iostream>

void subGrid();

int main()
{
	int count = 1;
	for (int row = 0; row < 9; row+=3)
	{
	    for (int col = 0; col < 9; col +=3)
	    {
	        for (int rowSub = 1; rowSub <= 3; ++rowSub)
	        {
	            for (int colSub = 1; colSub <= 3; ++colSub)
	            {
	                int x = (rowSub + row);
	                int y = (colSub + col);
	                std::cout << "(" << x << "," << y << ")" << std::endl;

	                std::cout << count << std::endl;
	                count++;
	                //mainLayout->addWidget(inputs[row + col + rowSub + colSub], row, column);
	            }
	        }
	    }
	}

	return 0;
}