#include "input.h"
#include <QGridLayout>
#include <iostream>

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

void Input::keyPressEvent(QKeyEvent *event) {
    event->accept();
    if (event->key() == Qt::Key_1) {
        this->setText("1");
    }
    else if (event->key() == Qt::Key_2) {
        this->setText("2");
    }
    else if (event->key() == Qt::Key_3) {
        this->setText("3");
    }
    else if (event->key() == Qt::Key_4) {
        this->setText("4");
    }
    else if (event->key() == Qt::Key_5) {
        this->setText("5");
    }
    else if (event->key() == Qt::Key_6) {
        this->setText("6");
    }
    else if (event->key() == Qt::Key_7) {
        this->setText("7");
    }
    else if (event->key() == Qt::Key_8) {
        this->setText("8");
    }
    else if (event->key() == Qt::Key_9) {
        this->setText("9");
    }
    else if (event->key() == Qt::Key_0) {
        this->setText("");
    }

    // Delete the overlay
    emit keyPressed();
}
