#include <QFont>
#ifndef PRESETCONTENT_H
#define PRESETCONTENT_H


class FontPreset {
public:
    FontPreset();

    enum class Alignment {
        Left = 0,
        Middle = 1,
        Right = 2,
    };

    void setFont(const QFont);
    void setLineSpacing(int);
    void setAlignment(Alignment);

    int lineSpacing;
    Alignment alignment;
    QFont* font;

    void loadJson(QJsonDocument &);
    const QJsonDocument toJson();
};


#endif // PRESETCONTENT_H
