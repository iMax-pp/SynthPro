#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QGraphicsProxyWidget>
#include <QProgressBar>

class ProgressBarWidget : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    ProgressBarWidget(int minimum, int maximum, QGraphicsItem* parent);

public slots:
    void setValue(int);

private:
    QProgressBar* m_progressBar;
};


#endif // PROGRESSBARWIDGET_H
