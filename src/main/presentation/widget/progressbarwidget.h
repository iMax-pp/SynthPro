#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QGraphicsProxyWidget>
#include <QProgressBar>

class ProgressBarWidget : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    ProgressBarWidget(QGraphicsItem* parent, int minimum = 0, int maximum = 100);

public slots:
    void setValue(int);
    void setMaximum(int);

private:
    QProgressBar* m_progressBar;
};


#endif // PROGRESSBARWIDGET_H
