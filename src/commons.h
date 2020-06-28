#include <QStringList>
#include <filesystem>
#ifndef COMMONS_H
#define COMMONS_H

#endif // COMMONS_H

#include "src/files/PresetContent/presetcontent.h"

namespace fs = std::__fs::filesystem;

fs::path textsDirectory();
fs::path fontPresetsDir();

QStringList getTextFileList();
QString readTextFile(const QString &filename);
void saveTextFile(const QString &filename, const QString &content);

QStringList getPresetNames();
PresetContent getPresetContent(const QString &presetName);
void savePresetContent(PresetContent &presetContent, const QString &presetName);
