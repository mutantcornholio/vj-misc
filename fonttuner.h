#ifndef FONTTUNER_H
#define FONTTUNER_H

#include <QWidget>
#include "statussender.h"
#include "commons.h"

namespace Ui {
class FontTuner;
}

class FontTuner : public QWidget, public StatusSenderBearer
{
    Q_OBJECT

public:
    explicit FontTuner(QWidget *parent = nullptr);
    ~FontTuner();
    const QFont& currentFont();

signals:
    void fontUpdated(const QFont&);
    void lineSpacingUpdated(int);

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

private:
    Ui::FontTuner *ui;
    QFont currentFontValue;
    int fontSize;
    int letterSpacing;
    int lineSpacing;
    int wordSpacing;
    bool bold;
    bool italic;
    bool underline;

    void updateFont();
    void loadPreset(const QString&);
};

#endif // FONTTUNER_H
