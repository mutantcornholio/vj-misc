#include "vjtextdocument.h"
#include <QRectF>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QDebug>
#include <QTextBlock>


VJTextDocument::VJTextDocument()
{
}

void VJTextDocument::drawContents(QPainter *p, const QRect &rect)
{
    p->save();
    QAbstractTextDocumentLayout::PaintContext ctx;

    ctx.palette.setColor(QPalette::Text, p->pen().color());

    for (QTextBlock block = this->begin(); block.isValid(); block = block.next()) {

        QTextCursor tc = QTextCursor(block); QTextBlockFormat fmt = block.blockFormat();

        if (fmt.topMargin() != this->lineSpacing || fmt.bottomMargin() != this->lineSpacing) {
            fmt.setTopMargin(this->lineSpacing);
            fmt.setBottomMargin(this->lineSpacing);
            tc.setBlockFormat(fmt);
        }
    }

    if (rect.isValid())
    {
        p->setClipRect(rect);
        ctx.clip = rect;
    }

    this->documentLayout()->draw(p, ctx);
    p->restore();
}

void VJTextDocument::setLineSpacing(int lineSpacing)
{
    this->lineSpacing = lineSpacing;
}
