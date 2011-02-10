#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QGraphicsWidget>

class TextWidget : public QGraphicsWidget {
public:
    TextWidget(const QString& text, QGraphicsItem* parent);

    inline const QString text() const { return m_textitem.text(); }
    inline void setText(const QString& text) { m_textitem.setText(text); }
    void setFont(const QFont&);

private:
    QGraphicsSimpleTextItem m_textitem;
};

#endif // TEXTWIDGET_H
