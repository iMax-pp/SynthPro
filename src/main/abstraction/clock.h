#ifndef CLOCK_H
#define CLOCK_H

#include <QMap>
#include <QObject>

class Module;
class QTimer;

/**
  * This class manages timers in order to trigger actions
  * that has been registered.
  *
  * This class implements the Singleton design pattern. An
  * instance can be given through the instance() method.
  */
class Clock : public QObject {
    Q_OBJECT
public:
    ~Clock();

    static Clock& instance();

    /**
      * Register a Module to a Fast Clock. Will call its
      * timerExpired() slot when its timer is expired.
      */
    void registerFastClock(Module*);
    // void registerSlowClock(Module*); // TODO

    /**
      * Unregister a module, stop the timer it was related to.
      */
    void unregister(Module*);

private:
    static const int FAST_TIMER_DELAY = 5;
    static const int SLOW_TIMER_DELAY = 50;

    explicit Clock(QObject *parent = 0);
    Clock(Clock&);

    QMap<Module*, QTimer*> m_fastTimers;
    QMap<Module*, QTimer*> m_slowTimers;
};

#endif // CLOCK_H
