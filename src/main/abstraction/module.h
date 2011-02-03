#ifndef MODULE_H
#define MODULE_H

class Module
{
public:
    Q_OBJECT
    Module(QObject* parent=0);
    virtual QList<Out> outports() const;
    virtual QList<In> inports() const;
    virtual void process()=0 ;

private:
    QList<Out> outports ;
    QList<In> inports ;
};

#endif // MODULE_H
