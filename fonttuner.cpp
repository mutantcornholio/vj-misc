#include <QDebug>
#include <QListIterator>
#include <QJsonDocument>

#include "fonttuner.h"
#include "ui_fonttuner.h"

FontTuner::FontTuner(QWidget *parent) : QWidget(parent), ui(new Ui::FontTuner) {
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
        ui->lineSpacing, SIGNAL(valueChanged(int)),
        this, SLOT(lineSpacingChanged(int))
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
    connect(
        ui->presetSelectBox, SIGNAL(currentTextChanged(const QString&)),
        this, SLOT(presetChanged(const QString&))
    );
    connect(
        ui->savePresetButton, SIGNAL(clicked()),
        this, SLOT(presetSaveClicked())
    );

    QStringList presetNames = getPresetNames();
    ui->presetSelectBox->addItems(presetNames);

    if (presetNames.length() > 0) {
        this->loadPreset(presetNames[0]);
    }

    this->letterSpacing = ui->letterSpacing->value();
    this->wordSpacing = ui->wordSpacing->value();
    this->bold = ui->boldBox->isChecked();
    this->italic = ui->italicBox->isChecked();
    this->underline = ui->underlineBox->isChecked();
    this->fontSize = ui->fontSize->value();
    this->fontChanged(ui->fontBox->currentFont());

    this->lineSpacingChanged(ui->lineSpacing->value());
}

FontTuner::~FontTuner() {
    delete ui;
}

void FontTuner::fontChanged(const QFont& font) {
    this->currentFontValue = QFont(font);
    this->updateFont();
}

void FontTuner::fontSizeChanged(int fontSize) {
    this->fontSize = fontSize;
    this->updateFont();
}

void FontTuner::letterSpacingChanged(int spacingValue) {
    this->letterSpacing = spacingValue;
    this->updateFont();
}

void FontTuner::lineSpacingChanged(int spacingValue) {
    this->lineSpacing = spacingValue;
    emit this->lineSpacingUpdated(spacingValue);
}

void FontTuner::wordSpacingChanged(int spacingValue) {
    this->wordSpacing = spacingValue;
    this->updateFont();
}

void FontTuner::boldChanged(int) {
    this->bold = ui->boldBox->isChecked();
    this->updateFont();
}

void FontTuner::italicChanged(int) {
    this->italic = ui->italicBox->isChecked();
    this->updateFont();
}

void FontTuner::underlineChanged(int) {
    this->underline = ui->underlineBox->isChecked();
    this->updateFont();
}

void FontTuner::presetChanged(const QString &text) {
    ui->presetName->setText(text);
    this->loadPreset(text);
}

void FontTuner::presetSaveClicked() {
    QString presetName = ui->presetName->text();
    PresetContent preset;
    preset.setFont(this->currentFontValue);
    preset.setLineSpacing(this->lineSpacing);
    savePresetContent(preset, presetName);

    if (ui->presetSelectBox->currentText() != presetName) {
        ui->presetSelectBox->addItem(presetName);
        ui->presetSelectBox->setCurrentText(presetName);
    }
}

void FontTuner::updateFont() {
    this->currentFontValue.setPixelSize(this->fontSize);
    this->currentFontValue.setLetterSpacing(QFont::PercentageSpacing, qreal(this->letterSpacing));
    this->currentFontValue.setWordSpacing(qreal(this->wordSpacing));
    this->currentFontValue.setBold(this->bold);
    this->currentFontValue.setItalic(this->italic);
    this->currentFontValue.setUnderline(this->underline);

    emit this->fontUpdated(this->currentFontValue);
}

const QFont& FontTuner::currentFont() {
    return this->currentFontValue;
}

void FontTuner::loadPreset(const QString &presetName) {
    auto presetContent = getPresetContent(presetName);

    ui->fontBox->setCurrentFont(QFont(*presetContent.font));

    ui->fontSize->setValue(presetContent.font->pixelSize());
    ui->letterSpacing->setValue(presetContent.font->letterSpacing());
    ui->wordSpacing->setValue(presetContent.font->wordSpacing());
    ui->boldBox->setCheckState(presetContent.font->bold() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->italicBox->setCheckState(presetContent.font->italic() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->underlineBox->setCheckState(presetContent.font->underline() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    ui->lineSpacing->setValue(presetContent.lineSpacing);
}
