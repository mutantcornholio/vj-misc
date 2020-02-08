#include "fonttuner.h"
#include "ui_fonttuner.h"

FontTuner::FontTuner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontTuner)
{
    ui->setupUi(this);

    connect(
        ui->fontBox, SIGNAL(currentFontChanged(const QFont&)),
        this, SLOT(fontChanged(const QFont&))
    );
    connect(
        ui->fontSize, SIGNAL(valueChanged(int)),
        this, SLOT(fontSizeChanged(int))
    );
    connect(
        ui->letterSpacing, SIGNAL(valueChanged(int)),
        this, SLOT(letterSpacingChanged(int))
    );
    connect(
        ui->wordSpacing, SIGNAL(valueChanged(int)),
        this, SLOT(wordSpacingChanged(int))
    );
    connect(
        ui->boldBox, SIGNAL(stateChanged(int)),
        this, SLOT(boldChanged(int))
    );
    connect(
        ui->italicBox, SIGNAL(stateChanged(int)),
        this, SLOT(italicChanged(int))
    );
    connect(
        ui->underlineBox, SIGNAL(stateChanged(int)),
        this, SLOT(underlineChanged(int))
    );

    this->letterSpacing = ui->letterSpacing->value();
    this->wordSpacing = ui->wordSpacing->value();
    this->bold = ui->boldBox->isChecked();
    this->italic = ui->italicBox->isChecked();
    this->underline = ui->underlineBox->isChecked();
    this->fontSize = ui->fontSize->value();
    this->fontChanged(ui->fontBox->currentFont());
}

FontTuner::~FontTuner()
{
    delete ui;
}

void FontTuner::fontChanged(const QFont& font)
{
    this->currentFontValue = QFont(font);
    this->updateFont();
}

void FontTuner::fontSizeChanged(int fontSize)
{
    this->fontSize = fontSize;
    this->updateFont();
}

void FontTuner::letterSpacingChanged(int spacingValue)
{
    this->letterSpacing = spacingValue;
    this->updateFont();
}

void FontTuner::wordSpacingChanged(int spacingValue)
{
    this->wordSpacing = spacingValue;
    this->updateFont();
}

void FontTuner::boldChanged(int)
{
    this->bold = ui->boldBox->isChecked();
    this->updateFont();
}

void FontTuner::italicChanged(int)
{
    this->italic = ui->italicBox->isChecked();
    this->updateFont();
}

void FontTuner::underlineChanged(int)
{
    this->underline = ui->underlineBox->isChecked();
    this->updateFont();
}

void FontTuner::updateFont()
{
    this->currentFontValue.setPixelSize(this->fontSize);
    this->currentFontValue.setLetterSpacing(QFont::PercentageSpacing, qreal(this->letterSpacing));
    this->currentFontValue.setWordSpacing(qreal(this->wordSpacing));
    this->currentFontValue.setBold(this->bold);
    this->currentFontValue.setItalic(this->italic);
    this->currentFontValue.setUnderline(this->underline);

    emit this->fontUpdated(this->currentFontValue);
}

const QFont& FontTuner::currentFont()
{
    return this->currentFontValue;
}

/*
void FontTuner::lineSpacingChanged(int spacingValue)
{
    this->currentFontValue.setLetterSpacing(QFont::PercentageSpacing, qreal(spacingValue));
}
*/
//void letterSpacingChanged(int);
