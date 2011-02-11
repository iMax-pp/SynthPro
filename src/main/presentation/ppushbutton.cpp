#include "ppushbutton.h"

#include <QPushButton>

PPushButton::PPushButton(QString name, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    QPushButton* button = new QPushButton(name);
    button->setCheckable(true);
    button->setFlat(true);

    connect(button, SIGNAL(pressed()), this, SIGNAL(buttonPushed()));
    connect(button, SIGNAL(released()), this, SIGNAL(buttonReleased()));

    setWidget(button);
}
