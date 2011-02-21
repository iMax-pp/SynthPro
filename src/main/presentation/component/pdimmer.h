#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;
class QGroupBox;

/**
 * Abstract presentation of Dimmer.
 */
class PDimmer : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PDimmer(CDimmer*, const QString& name, QGraphicsItem* parent = 0);

    /// Define a fixed size for the item.
    void setSize(qreal width, qreal height);

    virtual void setValue(int) = 0;

protected:
    QGroupBox* m_box;

signals:
    /// Triggered when current value changed.
    void valueChanged(int);

public:
    /// Called by module when updating the dimmer title.
    void updateTitle(const QString&);

private:
    CDimmer* m_control;
    QString m_name;
};

#endif // PDIMMER_H
