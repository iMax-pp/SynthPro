    #include "clock.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/module.h"
#include "abstraction/sequencer.h"

#include <QAudioOutput>
#include <QTimer>

Clock::Clock(QObject* parent)
    : QObject(parent)
    , m_started(false)
    , m_internalTimer(new QTimer(this))
    , adp(AudioDeviceProvider::instance())
    , sequencer(Sequencer::instance())
{
    // Connect the Internal Timer to a Slot that will call the Sequencer.
    connect(m_internalTimer, SIGNAL(timeout()), this, SLOT(internalTimerExpired()));
}

Clock::Clock(Clock& clock)
    : QObject(clock.parent())
    , m_started(false)
    , m_internalTimer(new QTimer(this))
    , adp(AudioDeviceProvider::instance())
    , sequencer(Sequencer::instance())
{
}

Clock::~Clock()
{
}

Clock& Clock::instance()
{
    static Clock instance;
    return instance;
}

void Clock::start()
{
    if (!m_started) {
        // If no Fast Timers are present, we only start the Internal one.
        if (m_fastTimers.count() == 0) {
            m_internalTimer->start(INTERNAL_TIMER_DELAY);
        } else {
            foreach (QTimer* timer, m_fastTimers.values()) {
                timer->start(FAST_TIMER_DELAY);
            }
        }

        m_started = true;
    }
}

void Clock::pause()
{
    if (m_started) {
        m_internalTimer->stop();
        foreach (QTimer* timer, m_fastTimers.values()) {
            timer->stop();
        }
        m_started = false;
    }
}

bool Clock::isStarted() const
{
    return m_started;
}

void Clock::registerFastClock(Module* module)
{
    // First we stop the Internal Timer, as we use instead a Fast Timer.
    m_internalTimer->stop();

    QTimer* timer = new QTimer(this);
    m_fastTimers.insert(module, timer);
    connect(timer, SIGNAL(timeout()), module, SLOT(timerExpired()));

    // Part of the unsuccessful attempt to manage the soundcard output from the Clock.
    // connect(timer, SIGNAL(timeout()), this, SLOT(soundCardTimerExpired()));

    // Start the newly registered timer if the Clock is started.
    if (m_started) {
        timer->start(FAST_TIMER_DELAY);
    }
}

void Clock::unregister(Module* module)
{
    if (m_fastTimers.contains(module)) {
        m_fastTimers.value(module)->stop();
        m_fastTimers.remove(module);
    }

    // If there are no more Fast Timers, we restart the Internal Timer.
    if (m_fastTimers.count() == 0) {
        m_internalTimer->start(FAST_TIMER_DELAY);
    }
}

void Clock::internalTimerExpired()
{
    sequencer.process();
}

/*
void Clock::soundCardTimerExpired()
{
    // Test if the sound card need data.
    int iteration = 0;
    int previousNbBytesNeededByOutput = 0;
    int nbBytesNeededByOutput = adp.audioOutput()->bytesFree();
    while (((iteration < SOUNDCARD_MAX_ITERATIONS) && (nbBytesNeededByOutput > 0))
         && (previousNbBytesNeededByOutput != nbBytesNeededByOutput) ) {

        sequencer.process();

        previousNbBytesNeededByOutput = nbBytesNeededByOutput;
        nbBytesNeededByOutput = adp.audioOutput()->bytesFree();

        iteration++;
    }

    if (iteration >= SOUNDCARD_MAX_ITERATIONS) {
        qWarning() << "Unable to feed the sound card enough !";
    }
}
*/
