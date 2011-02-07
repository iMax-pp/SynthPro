#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>

class Selector : public QObject
{
    Q_OBJECT
public:
    Selector(QList<int> shapes,int default_choice,QObject *parent = 0);
    int choice();
    void setChoice(int);
signals:

public slots:

private:
     QList<int> m_shapes ;
     int m_choice ;


};

#endif // SELECTOR_H
