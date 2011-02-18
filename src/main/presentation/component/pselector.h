#ifndef PSELECTOR_H
#define PSELECTOR_H

#include <QButtonGroup>
#include <QGraphicsProxyWidget>

/**
 * Presentation of Selector.
 */
class PSelector : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PSelector(QList<QString> items, const QString& name, QGraphicsItem* parent = 0);

public slots:
    /// Called to change the selected item.
    void selectButton(int idx);

signals:
    /// Triggered when the selected item has been changed.
    void choiceChanged(int);

private:
    QButtonGroup* m_buttonGroup;
};

#endif // PSELECTOR_H
