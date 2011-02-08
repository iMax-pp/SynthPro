#ifndef WAVEGENERATORFACTORY_H
#define WAVEGENERATORFACTORY_H

#include <QHash>

class WaveGenerator;

/**
*  This factory instantiate WaveGenerators according to a WaveType value given as parameter of the getWaveGenerator method
*/
class WaveGeneratorFactory {
public:
    /*
     * Enumeration of wave types.
     */
    enum WaveType {
        SawWave = 0,
        SinusWave,
        SquareWave,
        TriangleWave,
        DummyWave
    };
protected:
    QHash<int, WaveType> m_selectorConversionMap;

public:
    WaveGeneratorFactory();
    WaveGenerator* getWaveGenerator(WaveType);
    QHash<int, WaveType>* selectorConversionmap();
};
#endif // WAVEGENERATORFACTORY_H
