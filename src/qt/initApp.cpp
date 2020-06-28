#include <filesystem>
#include <QDebug>

#include "src/qt/commons.h"

namespace fs = std::__fs::filesystem;


void ensureDirs() {
    fs::create_directories(textsDirectory());
    fs::create_directories(fontPresetsDir());

    std::vector<std::string> presets;
}
