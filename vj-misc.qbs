import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile

Project{
    property string of_root: "/Applications/of_v0.10.1_osx_release"

    QtGuiApplication {

        name: "vj-misc"

        files: [
            "commons.cpp",
            "commons.h",
            "defines.cpp",
            "initApp.cpp",
            "initApp.h",
            "main.cpp",
            "mainwindow.cpp",
            "mainwindow.h",
            "presetcontent.cpp",
            "presetcontent.h",
            "qsyphonserver.h",
            "qsyphonserver.mm",
            "textglwidget.cpp",
            "textglwidget.h",
            "mainwindow.ui",
            "fonttuner.cpp",
            "fonttuner.h",
            "fonttuner.ui",
            "statussender.h",
            "statussender.cpp",
            "vjtextdocument.cpp",
            "vjtextdocument.h",
        ]

        Depends{
            name: "cpp"
        }

        cpp.frameworkPaths: ["libs/Syphon/lib/osx"]
        cpp.frameworks: ["cocoa", "opengl", "Syphon"]
        cpp.includePaths: [product.sourceDirectory]
        cpp.minimumMacosVersion: "10.15"

        Depends {
            name: "Qt"
            submodules: ["core", "gui", "widgets"] // Add more here if needed
        }
    }
}
