#include <QFont>
#ifndef PRESETCONTENT_H
#define PRESETCONTENT_H


class PresetContent {
public:
    PresetContent();

    void setFont(const QFont&);
    void setLineSpacing(int);

    int lineSpacing;
    QFont *font;

    void loadJson(QJsonDocument &);
    const QJsonDocument toJson();
};


#endif // PRESETCONTENT_H
