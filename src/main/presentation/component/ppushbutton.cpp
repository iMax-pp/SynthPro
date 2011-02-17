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
    m_button->setFixedSize(22, 22);
    m_button->setIcon(icon);
    setMaximumSize(m_button->size());
}

void PPushButton::setEnabled(bool enabled)
{
    m_button->setEnabled(enabled);
}

void PPushButton::setCheckable(bool checkable)
{
    m_button->setCheckable(checkable);
}

void PPushButton::setChecked(bool checked)
{
    m_button->setChecked(checked);
}

void PPushButton::setFlat(bool flat)
{
    m_button->setFlat(flat);
}
