#ifndef FONTTUNER_H
#define FONTTUNER_H

#include <QWidget>
#include <QButtonGroup>
#include "src/qt/ui/StatusSender/statussender.h"
#include "src/qt/FontPreset/fontpreset.h"
#include "src/qt/commons.h"

namespace Ui {
class FontTuner;
}

class FontTuner : public QWidget, public StatusSenderBearer {
    Q_OBJECT

public:
    explicit FontTuner(QWidget *parent = nullptr);
    ~FontTuner();
    const QFont& currentFont();

signals:
    void fontUpdated(const QFont&);
    void lineSpacingUpdated(int);
    void alignmentUpdated(FontPreset::Alignment);

private slots:
    void fontChanged(const QFont&);
    void fontSizeChanged(int);
    void lineSpacingChanged(int);
    void letterSpacingChanged(int);
    void wordSpacingChanged(int);
    void boldChanged(int);
    void italicChanged(int);
    void underlineChanged(int);
    void presetChanged(const QString&);
    void presetSaveClicked();
    void alignChanged(int, bool);

private:
    Ui::FontTuner *ui;
    FontPreset *preset;

    void readPresetFromUI();
    void setUIFromPreset();

    void emitFontUpdate();
    void emitAlignmentUpdate();
    void emitLineSpacingUpdate();
    void selectAlignmentRadiobutton();
    QButtonGroup *alignRadioGroup;
};

#endif // FONTTUNER_H
