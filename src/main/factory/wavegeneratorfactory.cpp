#include "wavegeneratorfactory.h"

#include "abstraction/wavegenerator.h"
#include "abstraction/wavegeneratordummy.h"
#include "abstraction/wavegeneratorsaw.h"
#include "abstraction/wavegeneratorsinus.h"
#include "abstraction/wavegeneratorsquare.h"
#include "abstraction/wavegeneratortriangle.h"

WaveGeneratorFactory::WaveGeneratorFactory()
{
    m_selectorConversionMap.insert(0, "SawWave");
    m_selectorConversionMap.insert(1, "SinusWave");
    m_selectorConversionMap.insert(2, "SquareWave");
    m_selectorConversionMap.insert(3, "TriangleWave");
    m_selectorConversionMap.insert(4, "DummyWave");

}

WaveGenerator* WaveGeneratorFactory::createWaveGenerator(const QString& waveType)
{
    if (waveType == "SawWave") {
        return new WaveGeneratorSaw();
    }

    if (waveType == "SinusWave") {
        return new WaveGeneratorSinus();
    }

    if (waveType == "SquareWave") {
        return new WaveGeneratorSquare();
    }

    if (waveType == "TriangleWave") {
        return new WaveGeneratorTriangle();
    }

    return new WaveGeneratorDummy();
}

QHash<int, QString>& WaveGeneratorFactory::selectorConversionMap()
{
    return m_selectorConversionMap;
}
