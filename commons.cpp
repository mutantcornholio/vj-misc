#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace fs = std::__fs::filesystem;

const char* homedir()
{
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
}

fs::path* textsDir()
{

    fs::path *dirPath = new fs::path(homedir());
    *dirPath /= ".vj-misc";
    *dirPath /= "texts";

    return dirPath;
}

fs::path* fontPresetsDir()
{

    fs::path *dirPath = new fs::path(homedir());
    *dirPath /= ".vj-misc";
    *dirPath /= "presets";

    return dirPath;
}
