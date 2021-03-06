#ifndef CLOCK_H
#define CLOCK_H

#include <QMap>
#include <QObject>

// class AudioDeviceProvider; // Used for the unsuccesful attempt to manage the soundcard output from the Clock.
class TimeCriticalModule;
class QTimer;
class Sequencer;

/**
 * This class manages timers in order to trigger actions
 * that has been registered.
 *
 * The principle is that is it possible to register to a Fast Timer,
 * which should be only used by one entity at the same time (like the
 * Speaker). This delegates the call to the Sequencer to the entity.
 *
 * However, if no Fast Timer is used, it means that we don't need
 * any Fast Timer, and the Internal Timer is used, a little slower,
 * that will call the Sequencer. This is useful to trigger the
 * module chain if there's no Speaker, like the Oscilloscope
 * or a WAVRecorder.
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
     * Start or resume the Timers.
     */
    void start();

    /**
     * Pause the Timers. They can be resumed with start().
     */
    void pause();

    /**
     * Returns the state of the clock.
     */
    bool isStarted() const;

    /**
     * Register a Time Critical Module to a Fast Timer. Will call its
     * fastTimerExpired() slot when its timer is expired.
     */
    void registerFastTimer(TimeCriticalModule*);

    /**
     * Unregister a Time Critical Module, stop the timer it was related to.
     */
    void unregisterFastTimer(TimeCriticalModule*);

private slots:
    /**
     * When the Internal Timer is expired, call the Sequencer.
     */
    void internalTimerExpired();

    /**
     * When a SoundCard Timer is expired, may call the Sequencer
     * several times in order to feed the sound card enough.
     * Part of the unsuccessful attempt to manage the soundcard
     * output from the Clock.
     */
    // void soundCardTimerExpired();

private:
    static const int FAST_TIMER_DELAY = 5; // For fast operations (sound card output).
    static const int INTERNAL_TIMER_DELAY = 30; // For non critical operations.

    // Part of the unsuccessful attempt to manage the soundcard
    // output from the Clock.
    // static const int SOUNDCARD_MAX_ITERATIONS = 10;

    bool m_started; // Indicates if the Timers are started or paused.

    explicit Clock(QObject* parent = 0);
    Clock(Clock&);

    QMap<TimeCriticalModule*, QTimer*> m_fastTimers;
    QTimer* m_internalTimer;
    // AudioDeviceProvider& adp; // Used for the unsuccesful attempt to manage the soundcard output from the Clock.
    Sequencer& sequencer;
};

#endif // CLOCK_H
