#include "progressbarwidget.h"

ProgressBarWidget::ProgressBarWidget(int minimum, int maximum, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    m_progressBar = new QProgressBar();
    m_progressBar->setRange(minimum, maximum);
    m_progressBar->setValue(0);

    setWidget(m_progressBar);
}

void ProgressBarWidget::setValue(int value)
{
    m_progressBar->setValue(value);
}
