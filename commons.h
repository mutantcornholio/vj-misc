#include <QStringList>
#include <filesystem>
#ifndef COMMONS_H
#define COMMONS_H

#endif // COMMONS_H

#include "presetcontent.h"

namespace fs = std::__fs::filesystem;

fs::path textsDir();
fs::path fontPresetsDir();
QStringList getPresetNames();
PresetContent getPresetContent(const QString &presetName);
void savePresetContent(PresetContent &presetContent, const QString &presetName);
