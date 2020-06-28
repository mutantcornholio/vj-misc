#ifndef VJTEXTDOCUMENT_H
#define VJTEXTDOCUMENT_H

#include <QTextDocument>

class VJTextDocument : public QTextDocument
{
    Q_OBJECT

public Q_SLOTS:
    void setLineSpacing(int lineSpacing);

public:
    VJTextDocument();
    void drawContents(QPainter *p, const QRect &rect = QRect());

private:
    int lineSpacing = 0;
};

#endif // VJTEXTDOCUMENT_H
