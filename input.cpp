#include "input.h"

Input::Input(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize Input::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += buttonSize;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
