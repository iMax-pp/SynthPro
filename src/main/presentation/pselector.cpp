#include "pselector.h"
#include "pselector.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QSignalMapper>
#include <QVBoxLayout>

PSelector::PSelector(QList<QString> items, const QString& name, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    // Create a group of buttons.
    QGroupBox* group = new QGroupBox(name);
    group->setFlat(true);

    // In a vertical layout.
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMargin(0);

    // Use a signal mapper to handle multiple buttons to one selector.
    QSignalMapper* signalMapper = new QSignalMapper(this);

    // And for each button, add it to the layout, connect it to the signalMapper.
    foreach (QString item, items) {
        QRadioButton* button = new QRadioButton(item);
        vbox->addWidget(button);

        signalMapper->setMapping(button, items.indexOf(item));
        connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
    }

    // Add the layout to the group.
    group->setLayout(vbox);

    connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(choiceChanged(int)));

    // And finally add the widget to the proxy.
    setWidget(group);
}
