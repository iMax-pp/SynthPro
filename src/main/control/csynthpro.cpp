#include "csynthpro.h"

#include <QGraphicsScene>

CSynthPro::CSynthPro()
    : SynthPro()
    , m_presentation(0)
    , m_graphicsScene(new QGraphicsScene)
{
}

CSynthPro::~CSynthPro()
{
    if (m_presentation) {
        delete m_presentation;
    }

    // m_graphicsScene has no parent so we must destroy it ourselves.
    delete m_graphicsScene;
}

void CSynthPro::setPresentation(PSynthPro* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
    m_presentation->setGraphicsScene(m_graphicsScene);
}

PSynthPro* CSynthPro::getPresentation() const
{
    return m_presentation;
}

void CSynthPro::addModule(QString& moduleType)
{
    // TODO
    // for type in moduleTypes:
    //   if type equals moduleType:
    //     module = typeFactory()
    // add(module)
    // scene.add(module)
}
