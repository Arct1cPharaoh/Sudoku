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
    void generate();

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
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> answer;

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
