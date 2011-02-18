#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QGraphicsProxyWidget>
#include <QProgressBar>

/**
 * Widget only class (no PAC involved), representing a progress bar.
 */
class ProgressBarWidget : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    ProgressBarWidget(QGraphicsItem* parent, int minimum = 0, int maximum = 100);

public slots:
    /// Called when the value has changed when the progress bar needs to be updated.
    void setValue(int);
    /// Called when the maximum value has changed when the progress bar needs to be updated.
    void setMaximum(int);

private:
    QProgressBar* m_progressBar;
};


#endif // PROGRESSBARWIDGET_H
