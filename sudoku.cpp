#include "sudoku.h"
#include "input.h"
#include "remove.h"

#include <QGridLayout>
#include <QLineEdit>
#include <iostream> // Debug

#include <QProcess>
#include <QApplication>

// Style
#include <QSpacerItem>
#include <QFrame>

// Creates endless spacing horizontaly around board so it dosen't scale weirdly
void setupBounds(QGridLayout* mainLayout)
{
    QSpacerItem* horiRight;
    horiRight = new QSpacerItem(1000,1, QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addItem(horiRight,1,4);

    QSpacerItem* horiLeft;
    horiLeft = new QSpacerItem(1000,1, QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addItem(horiLeft,0,0);
}

// Main function
Sudoku::Sudoku(QWidget *parent) : QWidget(parent)
{
    grid = findBoard(answer);
    setWindowTitle(tr("Sudoku!"));

    mainLayout = new QGridLayout();
    setLayout(mainLayout);

    // Setup board
    boardLayout = new QGridLayout();
    boardLayout->setSpacing(0);
    boardLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(boardLayout, 1, 1);
    setupBounds(mainLayout);

    createGrid(boardLayout);

    operatorsLayout = new QGridLayout();
    mainLayout->addLayout(operatorsLayout, 1, 3);

    solveButton = createInput("Solve", SLOT(solve()));
    solveButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    operatorsLayout->addWidget(solveButton, 1, 1);

    Input* genButton;
    genButton = createInput("New", SLOT(generate()));
    genButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    operatorsLayout->addWidget(genButton, 2, 1);
}

// Adds in vertical lines
void addVerticalLines(int col, int rowSub, QGridLayout* currentGrid)
{
    // First left line
    if (col == 0)
    {
        QFrame* lineBefore = new QFrame();
        lineBefore->setGeometry(QRect());
        lineBefore->setFrameShape(QFrame::VLine); // Replace by VLine for vertical line
        currentGrid->addWidget(lineBefore,rowSub,0);
    }

    // Creates all other lines
    QFrame* line = new QFrame();
    line->setGeometry(QRect());
    line->setFrameShape(QFrame::VLine); // Replace by VLine for vertical line
    currentGrid->addWidget(line,rowSub,4);
}

// Adds in horizontal lines
void addHorizontalLines(int row, QGridLayout* currentGrid)
{
    // Iterate thrice because three lines
    for (int i = 1; i <= 3; ++i)
    {
        // TOp line
        if (row == 0)
        {
            QFrame* lineBefore = new QFrame();
            lineBefore->setGeometry(QRect());
            lineBefore->setFrameShape(QFrame::HLine); // Replace by VLine for vertical line
            currentGrid->addWidget(lineBefore,0,i);
        }

        // Creates all other lines
        QFrame* line = new QFrame();
        line->setGeometry(QRect());
        line->setFrameShape(QFrame::HLine); // Replace by VLine for vertical line
        currentGrid->addWidget(line,4,i);
    }
}

// Creates sudoku grid in a sub-grid style
void Sudoku::createGrid(QGridLayout *boardLayout)
{
    QGridLayout* subGrids[9];
    subGrids[0] = new QGridLayout();
    QGridLayout* currentGrid = subGrids[0];

    int gridCount = 0;
    int countInputs = 0;
    for (int row = 0; row < 9; row+=3)
        for (int col = 0; col < 9; col +=3)
        {
            for (int rowSub = 1; rowSub <= 3; ++rowSub)
            {
                for (int colSub = 1; colSub <= 3; ++colSub)
                {
                    int x = (rowSub + row);
                    int y = (colSub + col);
                    if (grid[x - 1][y - 1] == 0)
                        inputs[countInputs] = createInput("", SLOT(inputClicked()));
                    else
                        inputs[countInputs] = createSetInput(QString::number(grid[x - 1][y - 1]));
                    currentGrid->addWidget(inputs[countInputs], rowSub, colSub);
                    countInputs++;
                }
                addVerticalLines(col, rowSub, currentGrid);
            }
            addHorizontalLines(row, currentGrid);

            ++gridCount;
            boardLayout->addLayout(currentGrid, row, col);
            subGrids[gridCount] = new QGridLayout();
            currentGrid = subGrids[gridCount];
        }
}

// Select a number
void Sudoku::numSelect()
{
    // Find button
    Input* clicked = qobject_cast<Input*>(sender());
    Input* button = qobject_cast<Input*>(clicked->parent());

    // Replace text
    button->setText(clicked->text());

    // Delete the overlay
    for (int i = 0; i < 9; ++i)
        delete nums[i];
    delete subLayout;

    activeInput = false;
}

// Input button down
void Sudoku::inputClicked()
{
    // Check for active button
    if (activeInput)
    {
        // Delete the previous overlay
        for (int i = 0; i < 9; ++i)
            delete nums[i];
        delete subLayout;
    }
    activeInput = true;

    Input* clicked = qobject_cast<Input*>(sender());

    // Creating a new layer for buttons
    subLayout = new QGridLayout(clicked);
    subLayout->setSpacing(0);

    int i = 0;
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
        {
            nums[i] = createInput(QString::number(i + 1), SLOT(numSelect()));
            subLayout->addWidget(nums[i], row, col);
            ++i;
        }
}

// What happens when you win
void Sudoku::winState()
{
    solveButton->setText("Win");
    // Locks every button
    for (int i = 0; i < 81; ++i)
        inputs[i]->setEnabled(false);
}

// Check if the board is solved
void Sudoku::solve()
{
    int countInputs = 0;
    // Checks if every cel maches answer
    for (int row = 0; row < 9; row+=3)
        for (int col = 0; col < 9; col +=3)
            for (int rowSub = 1; rowSub <= 3; ++rowSub)
                for (int colSub = 1; colSub <= 3; ++colSub)
                {
                    int x = (rowSub + row);
                    int y = (colSub + col);

                    int inputNum = inputs[countInputs]->text().split(" ")[0].toInt();
                    // Check to se if something dosen't match
                    if (inputNum != answer[x - 1][y - 1])
                    {
                        solveButton->setText("Not yet");
                        return;
                    }
                    countInputs++;
                }
    winState();
}

// Generates new board
void Sudoku::generate()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

// Creates an input button
Input* Sudoku::createInput(const QString &text, const char *member)
{
    Input* input = new Input(text);
    connect(input, SIGNAL(clicked()), this, member);
    return input;
}

// Creates non-usable input button
Input* Sudoku::createSetInput(const QString &text)
{
    Input* set = new Input(text);
    set->setEnabled(false);
    return set;
}
