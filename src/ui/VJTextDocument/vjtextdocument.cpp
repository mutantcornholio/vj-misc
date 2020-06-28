#include <QRectF>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QDebug>
#include <QTextBlock>

#include "vjtextdocument.h"
#include "src/defines.cpp"

VJTextDocument::VJTextDocument() {
}

Qt::Alignment convertAlignment(FontPreset::Alignment alignment) {
    switch (alignment) {
        case FontPreset::Alignment::Left : return Qt::AlignLeft;
        case FontPreset::Alignment::Middle : return Qt::AlignHCenter;
        case FontPreset::Alignment::Right : return Qt::AlignRight;
    }
}

void VJTextDocument::drawContents(QPainter *p, const QRect &rect) {
    p->save();
    QAbstractTextDocumentLayout::PaintContext ctx;

    ctx.palette.setColor(QPalette::Text, p->pen().color());

    this->setTextWidth(RENDERSIZE_X);
//    this->setUseDesignMetrics(true);


    for (QTextBlock block = this->begin(); block.isValid(); block = block.next()) {

        QTextCursor tc = QTextCursor(block); QTextBlockFormat fmt = block.blockFormat();

        if (
                fmt.topMargin() != this->lineSpacing
                || fmt.bottomMargin() != this->lineSpacing
                || fmt.alignment() != convertAlignment(this->alignment)
        ) {
            fmt.setTopMargin(this->lineSpacing);
            fmt.setBottomMargin(this->lineSpacing);
            fmt.setAlignment(convertAlignment(this->alignment));
            tc.setBlockFormat(fmt);
        }
    }
    this->adjustSize();

    if (rect.isValid()) {
        p->setClipRect(rect);
        ctx.clip = rect;
    }

    this->documentLayout()->draw(p, ctx);
    p->restore();
}

void VJTextDocument::setLineSpacing(int lineSpacing) {
    this->lineSpacing = lineSpacing;
}

void VJTextDocument::setAlignment(FontPreset::Alignment alignment) {
    this->alignment = alignment;
}
