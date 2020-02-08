#ifndef VJTEXTDOCUMENT_H
#define VJTEXTDOCUMENT_H

#include <QTextDocument>

class VJTextDocument : public QTextDocument
{
    Q_OBJECT

public:
    VJTextDocument();
    void drawContents(QPainter *p, const QRect &rect = QRect());
};

#endif // VJTEXTDOCUMENT_H
