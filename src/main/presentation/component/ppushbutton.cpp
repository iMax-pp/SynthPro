#include "ppushbutton.h"

#include <QPushButton>

PPushButton::PPushButton(QString name, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    m_button = new QPushButton(name);

    connect(m_button, SIGNAL(pressed()), this, SIGNAL(buttonPushed()));
    connect(m_button, SIGNAL(released()), this, SIGNAL(buttonReleased()));

    setWidget(m_button);
}

void PPushButton::setIcon(const QIcon& icon)
{
    m_button->setText("");
    m_button->setIcon(icon);
    m_button->setFixedSize(20, 20);
    setMaximumSize(m_button->size());
}
