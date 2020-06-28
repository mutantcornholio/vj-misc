Module {
    name: "fonttuner"

    files: [
        "fonttuner.cpp",
        "fonttuner.h",
        "fonttuner.ui",
    ]
    Depends {
        name: "Qt"
        submodules: ["core", "gui", "widgets"] // Add more here if needed
    }
}
