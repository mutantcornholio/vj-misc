#include "vjtextdocument.h"
#include <QRectF>
#include <QAbstractTextDocumentLayout>
#include <QPainter>

VJTextDocument::VJTextDocument()
{
}

void VJTextDocument::drawContents(QPainter *p, const QRect &rect)
{
    p->save();
    QAbstractTextDocumentLayout::PaintContext ctx;

    ctx.palette.setColor(QPalette::Text, p->pen().color());

    if (rect.isValid())
    {
        p->setClipRect(rect);
        ctx.clip = rect;
    }

    this->documentLayout()->draw(p, ctx);
    p->restore();

}
