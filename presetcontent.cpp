#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFont>

#include "presetcontent.h"


PresetContent::PresetContent() {
    this->font = new QFont();
    this->lineSpacing = 0;
}

void PresetContent::setFont(const QFont &font) {
    delete this->font;
    this->font = new QFont(font);
}

void PresetContent::setLineSpacing(int lineSpacing) {
    this->lineSpacing = lineSpacing;
}

void PresetContent::loadJson(QJsonDocument &doc) {
    delete this->font;
    this->font = new QFont();
    this->font->setFamily(doc["fontFamily"].toString("Arial"));
    this->lineSpacing = doc["lineSpacing"].toInt(0);
    this->font->setPixelSize(doc["fontSize"].toInt(100));
    this->font->setLetterSpacing(QFont::PercentageSpacing, doc["letterSpacing"].toInt(100));
    this->font->setWordSpacing(doc["wordSpacing"].toInt(1));
    this->font->setBold(doc["bold"].toBool());
    this->font->setItalic(doc["italic"].toBool());
    this->font->setUnderline(doc["underline"].toBool());
}

const QJsonDocument PresetContent::toJson() {
    QJsonObject obj
    {
        {"lineSpacing", this->lineSpacing},
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
