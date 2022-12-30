#ifndef SUDOKU_H
#define SUDOKU_H

#include <utility>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QGridLayout;
QT_END_NAMESPACE
class Input;

class Sudoku : public QWidget
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);

private slots:
    void numSelect();
    void inputClicked();
    void solve();

private:
    // Main layouts
    QGridLayout* mainLayout;
    QGridLayout* operatorsLayout;
    QGridLayout *boardLayout;

    // Setup
    void createGrid(QGridLayout *boardLayout);

    // Button making
    Input* createInput(const QString &text, const char *member);
    Input* createSetInput(const QString &text);

    // Grid and answer
    // Might come from somewhere else in furture, temporary
    std::vector<std::vector<int>> grid{{0,0,5,3,6,0,4,0,0},
                                       {9,6,2,0,0,4,0,7,0},
                                       {3,0,4,0,2,9,0,6,0},
                                       {8,2,0,9,4,0,0,1,3},
                                       {0,4,9,0,3,0,0,5,7},
                                       {0,0,0,2,0,0,9,8,0},
                                       {4,0,6,0,0,1,0,0,2},
                                       {0,0,0,6,9,3,0,0,5},
                                       {0,0,3,0,8,0,0,0,0,}};

    std::vector<std::vector<int>> answer{{1,8,5,3,6,7,4,2,9},
                                         {9,6,2,5,1,4,3,7,8},
                                         {3,7,4,8,2,9,5,6,1},
                                         {8,2,7,9,4,5,6,1,3},
                                         {6,4,9,1,3,8,2,5,7},
                                         {5,3,1,2,7,6,9,8,4},
                                         {4,9,6,7,5,1,8,3,2},
                                         {2,1,8,6,9,3,7,4,5},
                                         {7,5,3,4,8,2,1,9,6}};

    // Member Variables
    int NumInputs = 81;
    enum { squares = 9 };
    Input* inputs[81];

    bool activeInput = false;
    QGridLayout *subLayout;
    Input* nums[9];

    Input* solveButton;
    void winState();
};
#endif // SUDOKU_H
