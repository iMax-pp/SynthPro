#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;
class QGroupBox;

class PDimmer : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PDimmer(CDimmer*, const QString& name, int min, int max, int defaultValue,
            QGraphicsItem* parent = 0);

signals:
    void valueChanged(int);

private slots:
    void changeTitle(int);

private:
    CDimmer* m_control;
    QString m_name;
    QGroupBox* m_box;
};

#endif // PDIMMER_H
