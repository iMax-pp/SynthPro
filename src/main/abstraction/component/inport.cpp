#include "inport.h"

#include "abstraction/buffer.h"
#include "abstraction/component/connection.h"
#include "abstraction/component/outport.h"


InPort::InPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
{
}

void InPort::fetch()
{
    // We count only the connections that are actually connected to something !
    int nbConnectionUsed = connections().size();

    // If nothing is connected, clear the buffer.
    if (nbConnectionUsed == 0) {
        m_buffer.clear();
    } else {
        int size = m_buffer.length();

        // Scan all the connections to find those connected. The first one is simply duplicated.
        for (int noPass = 0; noPass < nbConnectionUsed; noPass++) {

            qreal* dataOut = m_buffer.data();
            qreal* dataIn = connections().at(noPass)->source()->buffer()->data();

            if (noPass == 0) {
                // First connexion found : we duplicate it.
                memcpy(dataOut, dataIn, sizeof(*m_buffer.data()) * m_buffer.length());
            } else {
                // The other connexions are added.
                for (int i = 0; i < size; i++) {
                    dataOut[i] += dataIn[i];
                }
            }
        }
    }

}
