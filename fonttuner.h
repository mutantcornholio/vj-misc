#ifndef FONTTUNER_H
#define FONTTUNER_H

#include <QWidget>
#include "statussender.h"

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

private slots:
    void fontChanged(const QFont&);
    void fontSizeChanged(int);
    //void lineSpacingChanged(int);
    void letterSpacingChanged(int);
    void wordSpacingChanged(int);
    void boldChanged(int);
    void italicChanged(int);
    void underlineChanged(int);

private:
    Ui::FontTuner *ui;
    QFont currentFontValue;
    int fontSize;
    int letterSpacing;
    int wordSpacing;
    bool bold;
    bool italic;
    bool underline;

    void updateFont();
};

#endif // FONTTUNER_H
