#include "wavegeneratorfactory.h"

#include "abstraction/wavegen/wavegenerator.h"
#include "abstraction/wavegen/wavegeneratordummy.h"
#include "abstraction/wavegen/wavegeneratorsaw.h"
#include "abstraction/wavegen/wavegeneratorsinus.h"
#include "abstraction/wavegen/wavegeneratorsquare.h"
#include "abstraction/wavegen/wavegeneratortriangle.h"

const QString WaveGeneratorFactory::Saw = QObject::tr("Saw");
const QString WaveGeneratorFactory::Sinus = QObject::tr("Sinus");
const QString WaveGeneratorFactory::Square = QObject::tr("Square");
const QString WaveGeneratorFactory::Triangle = QObject::tr("Triangle");

WaveGeneratorFactory::WaveGeneratorFactory()
{
    m_selectorConversionMap.insert(0, Saw);
    m_selectorConversionMap.insert(1, Sinus);
    m_selectorConversionMap.insert(2, Square);
    m_selectorConversionMap.insert(3, Triangle);
}

WaveGenerator* WaveGeneratorFactory::createWaveGenerator(const QString& waveType)
{
    if (waveType == Saw) {
        return new WaveGeneratorSaw();
    }

    if (waveType == Sinus) {
        return new WaveGeneratorSinus();
    }

    if (waveType == Square) {
        return new WaveGeneratorSquare();
    }

    if (waveType == Triangle) {
        return new WaveGeneratorTriangle();
    }

    return new WaveGeneratorSquare();
}

QHash<int, QString>& WaveGeneratorFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
