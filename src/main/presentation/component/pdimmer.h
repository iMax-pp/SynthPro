#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;
class QGroupBox;

class PDimmer : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PDimmer(CDimmer*, const QString& name, QGraphicsItem* parent = 0);

    void setSize(qreal width, qreal height);

protected:
    QGroupBox* m_box;

signals:
    void valueChanged(int);

protected slots:
    void changeTitle(int);

private:
    CDimmer* m_control;
    QString m_name;
};

#endif // PDIMMER_H
