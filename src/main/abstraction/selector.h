#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>

class Selector : public QObject {
    Q_OBJECT
public:
    Selector(QList<int>, int, QObject* parent = 0);
    int choice();
    void setChoice(int);

private:
     QList<int> m_choices;
     int m_choice;
};

#endif // SELECTOR_H
