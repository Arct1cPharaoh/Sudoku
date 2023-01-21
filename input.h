#ifndef INPUT_H
#define INPUT_H

#include <QToolButton>
#include <QFont>
#include <QKeyEvent>
#include "sudoku.h"

class Input : public QToolButton
{
    Q_OBJECT

public:
    explicit Input(const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const override;


    void keyPressEvent(QKeyEvent *event) override;

private:
    int buttonSize = 50;
    bool activeInput = false;
};

#endif // INPUT_H
