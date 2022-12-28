#include "sudoku.h"
#include "input.h"

#include <QGridLayout>
#include <QLineEdit>
#include <iostream> // Debug

// Style
#include <QSpacerItem>
#include <QLine>

void setupBounds(QGridLayout* mainLayout)
{
    QSpacerItem* hori;
    hori = new QSpacerItem(1000,1, QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addItem(hori,1,4);

    QSpacerItem* hori2;
    hori2 = new QSpacerItem(1000,1, QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addItem(hori2,0,0);
}

Sudoku::Sudoku(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Sudoku!"));

    mainLayout = new QGridLayout();
    setLayout(mainLayout);

    boardLayout = new QGridLayout();
    boardLayout->setSpacing(0);
    boardLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(boardLayout, 1, 1);
    createGrid(boardLayout);

    setupBounds(mainLayout);

    operatorsLayout = new QGridLayout();
    mainLayout->addLayout(operatorsLayout, 1, 3);
    solveButton = createInput("Solve", SLOT(solve()));
    solveButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    operatorsLayout->addWidget(solveButton, 1, 1);

}


void Sudoku::createGrid(QGridLayout *boardLayout)
{
    //Each Subset of inputs
    int countInputs = 0;
    for (int row = 0; row < 9; row+=3)
    {
        for (int col = 0; col < 9; col +=3)
        {
            for (int rowSub = 1; rowSub <= 3; ++rowSub)
                for (int colSub = 1; colSub <= 3; ++colSub)
                {
                    int x = (rowSub + row);
                    int y = (colSub + col);
                    if (grid[x - 1][y - 1] == 0)
                    {
                        inputs[countInputs] = createInput("", SLOT(inputClicked()));
                    }
                    else
                    {
                        inputs[countInputs] = createSetInput(QString::number(grid[x - 1][y - 1]));
                        inputs[countInputs]->setEnabled(false);
                    }
                    boardLayout->addWidget(inputs[countInputs], x, y);
                    countInputs++;
                }
        }
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

void Sudoku::winState()
{
    if (solved)
    {
        solveButton->setText("Win");
        for (int i = 0; i < 81; ++i)
            inputs[i]->setEnabled(false);
    }
    else
    {
        solveButton->setText("Not yet");
    }
}

void Sudoku::solve()
{
    solved = true;
    int countInputs = 0;
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

                    int inputNum = inputs[countInputs]->text().split(" ")[0].toInt();
                    if (inputNum != answer[x - 1][y - 1])
                    {
                        solved = false;
                        winState();
                        return;
                    }
                    countInputs++;
                }
            }
        }
    }

    winState();
}

Input* Sudoku::createInput(const QString &text, const char *member)
{
    Input* input = new Input(text);
    connect(input, SIGNAL(clicked()), this, member);
    return input;
}

Input* Sudoku::createSetInput(const QString &text)
{
    Input* set = new Input(text);
    return set;
}
