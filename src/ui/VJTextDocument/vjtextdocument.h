#ifndef VJTEXTDOCUMENT_H
#define VJTEXTDOCUMENT_H

#include <QTextDocument>
#include "src/FontPreset/fontpreset.h"

class VJTextDocument : public QTextDocument {
    Q_OBJECT

public Q_SLOTS:
    void setLineSpacing(int lineSpacing);
    void setAlignment(FontPreset::Alignment);

public:
    VJTextDocument();
    void drawContents(QPainter *p, const QRect &rect = QRect());

private:
    int lineSpacing = 0;
    FontPreset::Alignment alignment = FontPreset::Alignment::Left;
};

#endif // VJTEXTDOCUMENT_H
