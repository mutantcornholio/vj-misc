#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QDir>

#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <vector>
#include <fstream>

#include "presetcontent.h"


namespace fs = std::__fs::filesystem;

const char* homedir() {
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
}

fs::path textsDirectory() {

    fs::path dirPath = fs::path(homedir());
    dirPath /= ".vj-misc";
    dirPath /= "texts";

    return dirPath;
}

fs::path fontPresetsDir() {

    fs::path dirPath = fs::path(homedir());
    dirPath /= ".vj-misc";
    dirPath /= "presets";

    return dirPath;
}

bool isJson(const std::string &filename) {
    return filename.compare(filename.length() - 5, 5, ".json") == 0;
}


QStringList getPresetNames() {
    QStringList filters;
    filters << "*.json";

    QDir presetDir(fontPresetsDir().c_str());
    presetDir.setNameFilters(filters);
    presetDir.setFilter(QDir::Files);

    QStringList filenamesList = presetDir.entryList();
    QStringList presetNamesList;

    std::transform(
        filenamesList.begin(),
        filenamesList.end(),
        std::back_inserter(presetNamesList),
        [](QString entry) {return entry.chopped(5);}
    );

    return presetNamesList;
}

QString getPresetFileName(const QString &presetName) {
    fs::path filePath = fontPresetsDir();
    filePath /= presetName.toStdString();
    filePath += ".json";

    return QString(filePath.c_str());
}

PresetContent getPresetContent(const QString &presetName) {
    QFile jsonFile(getPresetFileName(presetName));
    jsonFile.open(QIODevice::ReadOnly);

    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    jsonFile.close();

    PresetContent content;
    content.loadJson(doc);

    return content;
}

void savePresetContent(PresetContent &presetContent, const QString &presetName) {
    QFile jsonFile(getPresetFileName(presetName));
    jsonFile.open(QIODevice::WriteOnly);
    jsonFile.write(presetContent.toJson().toJson());
    jsonFile.close();
}

QString getTextFileName(const QString &fileName) {
    fs::path filePath = textsDirectory();
    filePath /= fileName.toStdString();

    return QString(filePath.c_str());
}


QStringList getTextFileList() {
    QDir textsDir(textsDirectory().c_str());
    textsDir.setFilter(QDir::Files);

    QStringList filenamesList = textsDir.entryList();

    return filenamesList;
}

QString readTextFile(const QString &filename) {
    QFile textFile(getTextFileName(filename));
    textFile.open(QIODevice::ReadOnly);
    QString res(textFile.readAll());
    textFile.close();
    return res;
}

void saveTextFile(const QString &filename, const QString &content) {
    QFile textFile(getTextFileName(filename));
    textFile.open(QIODevice::WriteOnly);
    textFile.write(content.toUtf8());
    textFile.close();
}
