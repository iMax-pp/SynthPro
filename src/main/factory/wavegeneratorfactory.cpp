#include "wavegeneratorfactory.h"

#include "abstraction/wavegenerator.h"
#include "abstraction/wavegeneratordummy.h"
#include "abstraction/wavegeneratorsaw.h"
#include "abstraction/wavegeneratorsinus.h"
#include "abstraction/wavegeneratorsquare.h"
#include "abstraction/wavegeneratortriangle.h"

WaveGeneratorFactory::WaveGeneratorFactory()
{
    m_selectorConversionMap.insert(0, "Saw");
    m_selectorConversionMap.insert(1, "Sinus");
    m_selectorConversionMap.insert(2, "Square");
    m_selectorConversionMap.insert(3, "Triangle");
}

WaveGenerator* WaveGeneratorFactory::createWaveGenerator(const QString& waveType)
{
    if (waveType == "Saw") {
        return new WaveGeneratorSaw();
    }

    if (waveType == "Sinus") {
        return new WaveGeneratorSinus();
    }

    if (waveType == "Square") {
        return new WaveGeneratorSquare();
    }

    if (waveType == "Triangle") {
        return new WaveGeneratorTriangle();
    }

    return new WaveGeneratorSquare();
}

QHash<int, QString>& WaveGeneratorFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
