#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFont>

#include "src/qt/FontPreset/fontpreset.h"


FontPreset::FontPreset() {
    this->lineSpacing = 0;
    this->alignment = Alignment::Left;
    this->font = new QFont();
}

void FontPreset::setFont(const QFont newFont) {
    QFont* font1 = new QFont(newFont);
    this->font->swap(*font1);
}

void FontPreset::setLineSpacing(int lineSpacing) {
    this->lineSpacing = lineSpacing;
}

void FontPreset::setAlignment(Alignment alignment) {
    this->alignment = alignment;
}

void FontPreset::loadJson(QJsonDocument &doc) {
    this->font->setFamily(doc["fontFamily"].toString("Arial"));
    this->font->setPixelSize(doc["fontSize"].toInt(100));
    this->font->setLetterSpacing(QFont::SpacingType::AbsoluteSpacing, doc["letterSpacing"].toInt(100));
    this->font->setWordSpacing(doc["wordSpacing"].toInt(1));
    this->font->setBold(doc["bold"].toBool());
    this->font->setItalic(doc["italic"].toBool());
    this->font->setUnderline(doc["underline"].toBool());

    this->alignment = Alignment(doc["alignment"].toInt(0));
    this->lineSpacing = doc["lineSpacing"].toInt(0);
}

const QJsonDocument FontPreset::toJson() {
    QJsonObject obj {
        {"lineSpacing", this->lineSpacing},
        {"alignment", int(this->alignment)},

        {"fontFamily", this->font->family()},
        {"fontSize", this->font->pixelSize()},
        {"letterSpacing", this->font->letterSpacing()},
        {"wordSpacing", this->font->wordSpacing()},
        {"bold", this->font->bold()},
        {"italic", this->font->italic()},
        {"underline", this->font->underline()},
    };

    return QJsonDocument(obj);
}
