#include "wavegeneratorfactory.h"

#include "abstraction/wavegenerator.h"
#include "abstraction/wavegeneratordummy.h"
#include "abstraction/wavegeneratorsaw.h"
#include "abstraction/wavegeneratorsinus.h"
#include "abstraction/wavegeneratorsquare.h"
#include "abstraction/wavegeneratortriangle.h"

WaveGeneratorFactory::WaveGeneratorFactory()
{
    m_selectorConversionMap.insert(0, SawWave);
    m_selectorConversionMap.insert(1, SinusWave);
    m_selectorConversionMap.insert(2, SquareWave);
    m_selectorConversionMap.insert(3, TriangleWave);
    m_selectorConversionMap.insert(4, DummyWave);

}

WaveGenerator* WaveGeneratorFactory::getWaveGenerator(WaveType waveType)
{
    switch (waveType) {
    case SawWave :
            return new WaveGeneratorSaw();
    case SinusWave :
            return new WaveGeneratorSinus();
    case SquareWave :
            return new WaveGeneratorSquare();
    case TriangleWave :
            return new WaveGeneratorTriangle();
    case DummyWave :
            return new WaveGeneratorDummy();
    default :
            return new WaveGeneratorDummy();
    }
}

QHash<int, WaveGeneratorFactory::WaveType>* WaveGeneratorFactory::selectorConversionmap()
{
    return &m_selectorConversionMap;
}
