#include <QDebug>
#include <QListIterator>
#include <QJsonDocument>
#include <QButtonGroup>

#include "fonttuner.h"
#include "ui_fonttuner.h"

FontTuner::FontTuner(QWidget *parent) : QWidget(parent), ui(new Ui::FontTuner) {
    this->preset = new FontPreset();
    ui->setupUi(this);

    this->alignRadioGroup = new QButtonGroup(this->ui->align);
    this->alignRadioGroup->addButton(this->ui->alignLeft, 0);
    this->alignRadioGroup->addButton(this->ui->alignMiddle, 1);
    this->alignRadioGroup->addButton(this->ui->alignRight, 2);
    this->alignRadioGroup->setExclusive(true);

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
    connect(
        this->alignRadioGroup, SIGNAL(idToggled(int, bool)),
        this, SLOT(alignChanged(int, bool))
    );

    QStringList presetNames = getPresetNames();
    ui->presetSelectBox->addItems(presetNames);

    if (presetNames.length() > 0) {
        loadPreset(presetNames[0], this->preset);
    }

    this->setUIFromPreset();
}

FontTuner::~FontTuner() {
    delete ui;
}

void FontTuner::emitFontUpdate() {
    emit this->fontUpdated(*this->preset->font);
}

void FontTuner::emitAlignmentUpdate() {
    emit this->alignmentUpdated(this->preset->alignment);
}

void FontTuner::emitLineSpacingUpdate() {
    emit this->lineSpacingUpdated(this->preset->lineSpacing);
}

void FontTuner::fontChanged(const QFont& font) {
    this->preset->font->setFamily(font.family());
    this->emitFontUpdate();
}

void FontTuner::fontSizeChanged(int fontSize) {
    this->preset->font->setPixelSize(fontSize);
    this->emitFontUpdate();
}

void FontTuner::letterSpacingChanged(int spacingValue) {
    this->preset->font->setLetterSpacing(QFont::SpacingType::AbsoluteSpacing, spacingValue);
    this->emitFontUpdate();
}

void FontTuner::wordSpacingChanged(int spacingValue) {
    this->preset->font->setWordSpacing(spacingValue);
    this->emitFontUpdate();
}

void FontTuner::boldChanged(int) {
    this->preset->font->setBold(ui->boldBox->isChecked());
    this->emitFontUpdate();
}

void FontTuner::italicChanged(int) {
    this->preset->font->setItalic(ui->italicBox->isChecked());
    this->emitFontUpdate();
}

void FontTuner::underlineChanged(int) {
    this->preset->font->setUnderline(ui->underlineBox->isChecked());
    this->emitFontUpdate();
}

void FontTuner::lineSpacingChanged(int spacingValue) {
    this->preset->setLineSpacing(spacingValue);
    this->emitLineSpacingUpdate();
}

void FontTuner::alignChanged(int id, bool checked) {
    if (!checked) {
        return;
    }
    this->preset->alignment = FontPreset::Alignment(id);
    this->emitAlignmentUpdate();
}

void FontTuner::presetChanged(const QString &text) {
    ui->presetName->setText(text);
    loadPreset(text, this->preset);
    this->setUIFromPreset();
}

void FontTuner::presetSaveClicked() {
    QString presetName = ui->presetName->text();
    savePreset(*this->preset, presetName);

    if (ui->presetSelectBox->currentText() != presetName) {
        ui->presetSelectBox->addItem(presetName);
        ui->presetSelectBox->setCurrentText(presetName);
    }
}

const QFont& FontTuner::currentFont() {
    return *this->preset->font;
}

void FontTuner::selectAlignmentRadiobutton() {
    switch (this->preset->alignment) {
        case FontPreset::Alignment::Left : ui->alignLeft->click(); break;
        case FontPreset::Alignment::Middle : ui->alignMiddle->click(); break;
        case FontPreset::Alignment::Right : ui->alignRight->click(); break;
    }
}

void FontTuner::readPresetFromUI() {
    this->preset->setAlignment(FontPreset::Alignment(this->alignRadioGroup->checkedId()));

    this->preset->font->setFamily(ui->fontBox->currentFont().family());
    this->preset->font->setLetterSpacing(QFont::SpacingType::AbsoluteSpacing, ui->letterSpacing->value());
    this->preset->font->setWordSpacing(ui->wordSpacing->value());
    this->preset->font->setBold(ui->boldBox->isChecked());
    this->preset->font->setItalic(ui->italicBox->isChecked());
    this->preset->font->setUnderline(ui->underlineBox->isChecked());

    this->emitFontUpdate();
    this->emitAlignmentUpdate();
    this->emitLineSpacingUpdate();
}

void FontTuner::setUIFromPreset() {
    this->selectAlignmentRadiobutton();

    ui->fontBox->setCurrentFont(QFont(*this->preset->font));
    ui->fontSize->setValue(this->preset->font->pixelSize());
    ui->letterSpacing->setValue(this->preset->font->letterSpacing());
    ui->wordSpacing->setValue(this->preset->font->wordSpacing());
    ui->boldBox->setCheckState(this->preset->font->bold() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->italicBox->setCheckState(this->preset->font->italic() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->underlineBox->setCheckState(this->preset->font->underline() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    ui->lineSpacing->setValue(this->preset->lineSpacing);
}
