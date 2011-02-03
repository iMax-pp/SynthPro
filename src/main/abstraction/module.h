#ifndef MODULE_H
#define MODULE_H

#include <QObject>

class In;
class Out;

class Module : public QObject {
public:
    Q_OBJECT
    Module(QObject* parent = 0);
    virtual QList<Out*>::const_iterator outports() const;
    virtual QList<In*>::const_iterator inports() const;
    virtual void process() = 0;

private:
    QList<Out*> m_outports;
    QList<In*> m_inports;
};

#endif // MODULE_H
