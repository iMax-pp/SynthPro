#include "selector.h"

Selector::Selector(QList<int> shapes,int default_choice,QObject *parent)
    : QObject(parent)
    , m_shapes(shapes)
    , m_choice(default_choice)

{
}
int Selector::choice()
{
    return m_choice ;
}
void Selector::setChoice(int choice){
    m_choice = choice ;
}
