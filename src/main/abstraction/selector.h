#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>
/*
* A selector allow to choose in a list of values an algorithm or a config value in a module
*/
class Selector : public QObject {
    Q_OBJECT
public:
    Selector(QList<int>, int, QObject* parent = 0);
    int choice() const;
    void setChoice(int);

private:
     QList<int> m_choices;
     int m_choice;
};

#endif // SELECTOR_H
