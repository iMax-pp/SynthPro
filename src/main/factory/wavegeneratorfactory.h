#ifndef WAVEGENERATORFACTORY_H
#define WAVEGENERATORFACTORY_H

#include <QHash>

class WaveGenerator;

/**
*  This factory instantiate WaveGenerators according to a QString value given as parameter of the createWaveGenerator method.
*/
class WaveGeneratorFactory {
public:
    WaveGeneratorFactory();

    WaveGenerator* createWaveGenerator(const QString&);
    QHash<int, QString>& selectorConversionMap();

    static const QString Saw;
    static const QString Sinus;
    static const QString Square;
    static const QString Triangle;
protected:
    QHash<int, QString> m_selectorConversionMap;
};
#endif // WAVEGENERATORFACTORY_H
