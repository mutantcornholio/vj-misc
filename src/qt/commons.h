#include <QStringList>
#include <filesystem>
#ifndef COMMONS_H
#define COMMONS_H

#endif // COMMONS_H

#include "src/qt/FontPreset/fontpreset.h"

namespace fs = std::__fs::filesystem;

fs::path textsDirectory();
fs::path fontPresetsDir();

QStringList getTextFileList();
QString readTextFile(const QString &filename);
void saveTextFile(const QString &filename, const QString &content);

QStringList getPresetNames();
void loadPreset(const QString&, FontPreset*);
void savePreset(FontPreset &presetContent, const QString &presetName);
