#include "input.h"

Input::Input(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
    QFont font = this->font();
    font.setPointSize(font.pointSize() + 8);
    this->setFont(font);
}

QSize Input::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += buttonSize;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
