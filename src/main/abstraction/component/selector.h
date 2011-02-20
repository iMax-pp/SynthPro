#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>

/**
 * A selector allow to choose in a list of values an algorithm or a config value in a module.
 */
class Selector : public QObject {
    Q_OBJECT

public:
    /// Constructs a Selector from a QList of choices and a defaultChoice.
    Selector(QList<int> choices, int defaultChoice, QObject* parent = 0);

    /// @returns The current choice.
    inline int choice() const { return m_choice; }

public slots:
    /// @param choice to set the selector to.
    void setChoice(int);

signals :
    /// Signal trigerred when choice is changed.
    void choiceChanged(int choice);

private:
    QList<int> m_choices;
    int m_choice;
};

#endif // SELECTOR_H
