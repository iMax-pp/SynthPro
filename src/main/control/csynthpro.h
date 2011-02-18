#ifndef CSYNTHPRO_H
#define CSYNTHPRO_H

#include "abstraction/synthpro.h"
#include "factory/synthprofactory.h"
#include "presentation/psynthpro.h"

#include <QPointer>

class CVirtualPort;
class QGraphicsScene;

/**
 * SynthPro control class (PAC by inheritance).
 */
class CSynthPro : public SynthPro {
    Q_OBJECT

public:
    explicit CSynthPro(SynthProFactory*);
    virtual ~CSynthPro();

    /// @returns the associated PSynthPro presentation.
    inline PSynthPro* presentation() const { return m_presentation; }

    /// @param presentation of type PSynthPro to associate with this CSynthPro.
    void setPresentation(PSynthPro*);

    /// Override SynthPro::add to add the presentation when Module is successfully added.
    void add(Module*);

    /// Create a new Module with the given ModuleType and at the given QPointF.
    void addModule(SynthProFactory::ModuleType, const QPointF&);

    /**
     * Show drag&drop feedback from given CVirtualPort to every single port.
     * @see hideFeedback
     */
    void showFeedback(CVirtualPort*);

    /**
     * Hide drag&drop feedback from given CVirtualPort to every single port.
     * @see showFeedback
     */
    void hideFeedback();

    /// Create a new scheme (delete every module).
    void newScheme();

private slots:
    /// Slot called when Play/Pause button is clicked.
    void play(bool);

private:
    QPointer<PSynthPro> m_presentation;
    QGraphicsScene* m_graphicsScene;
    SynthProFactory* m_factory;
};

#endif // CSYNTHPRO_H
