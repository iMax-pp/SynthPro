#include "clock.h"

#include "abstraction/module.h"
#include "abstraction/sequencer.h"
#include "abstraction/audiodeviceprovider.h"

#include <QAudioOutput>
#include <QDebug>
#include <QTimer>

Clock::Clock(QObject* parent)
    : QObject(parent)
    , m_started(false)
    , m_internalTimer(new QTimer(this))
{
    // Connect the Internal Timer to a Slot that will call the Sequencer.
    connect(m_internalTimer, SIGNAL(timeout()), this, SLOT(internalTimerExpired()));
}

Clock::Clock(Clock& clock)
    : QObject(clock.parent())
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
    qDebug("Clock::start");

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

void Clock::registerFastClock(Module* module)
{
    // First we stop the Internal Timer, as we use instead a Fast Timer.
    m_internalTimer->stop();

    QTimer* timer = new QTimer(this);
    m_fastTimers.insert(module, timer);
    connect(timer, SIGNAL(timeout()), this, SLOT(soundCardTimerExpired()));
    //connect(timer, SIGNAL(timeout()), module, SLOT(timerExpired()));

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
    Sequencer::instance().process();
}

void Clock::soundCardTimerExpired()
{
    // Test if the sound card need data.
    AudioDeviceProvider& adp = AudioDeviceProvider::instance();

    int iteration = 0;
    int previousNbBytesNeededByOutput = -1;
    int nbBytesNeededByOutput = adp.audioOutput()->bytesFree();
    while (((iteration < SOUNDCARD_MAX_ITERATIONS) && (nbBytesNeededByOutput > 0))
        && (previousNbBytesNeededByOutput != nbBytesNeededByOutput)) {
        // qDebug() << "IT = " << iteration << "NEED : " << nbBytesNeededByOutput;
        Sequencer::instance().process();

        previousNbBytesNeededByOutput = nbBytesNeededByOutput;
        nbBytesNeededByOutput = adp.audioOutput()->bytesFree();
        iteration++;
    }

    // qDebug() << "IT FINI = " << iteration;

    if (iteration >= SOUNDCARD_MAX_ITERATIONS) {
        qWarning() << "Unable to feed the sound card enough !";
    }
}
