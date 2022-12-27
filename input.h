#ifndef INPUT_H
#define INPUT_H

#include <QToolButton>

class Input : public QToolButton
{
    Q_OBJECT

public:
    explicit Input(const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const override;

private:
    int buttonSize = 75;
};

#endif // INPUT_H
