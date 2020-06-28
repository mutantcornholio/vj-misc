import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile

Project{
    QtGuiApplication {
        name: "vj-misc"
        type: ["application"]

        files: [
            "src/qt/commons.cpp",
            "src/qt/commons.h",
            "src/qt/defines.cpp",
            "src/qt/initApp.cpp",
            "src/qt/initApp.h",
            "src/qt/main.cpp",
            "src/qt/ui/MainWindow/mainwindow.cpp",
            "src/qt/ui/MainWindow/mainwindow.h",
            "src/qt/ui/MainWindow/mainwindow.ui",
            "src/qt/FontPreset/fontpreset.cpp",
            "src/qt/FontPreset/fontpreset.h",
            "src/qt/QSyphonServer/qsyphonserver.h",
            "src/qt/QSyphonServer/qsyphonserver.mm",
            "src/qt/ui/TextGLWidget/textglwidget.cpp",
            "src/qt/ui/TextGLWidget/textglwidget.h",
            "src/qt/ui/FontTuner/fonttuner.cpp",
            "src/qt/ui/FontTuner/fonttuner.h",
            "src/qt/ui/FontTuner/fonttuner.ui",
            "src/qt/ui/StatusSender/statussender.h",
            "src/qt/ui/StatusSender/statussender.cpp",
            "src/qt/ui/VJTextDocument/vjtextdocument.cpp",
            "src/qt/ui/VJTextDocument/vjtextdocument.h",

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

        Depends {
            name: "ib"
            condition: qbs.targetOS.contains("macos")
        }

        Properties {
            condition: qbs.targetOS.contains("macos")
            ib.appIconName: "VJMisc"
        }

        Group {
            name: "Icons (macOS)"
            condition: qbs.targetOS.contains("macos")
            files: [
                "vj-misc.xcassets",
            ]
        }

        Group {
            condition: qbs.targetOS.contains("osx")
            fileTagsFilter: ["infoplist"]
            qbs.install: true
            qbs.installSourceBase: product.buildDirectory
        }

        Group {
            name: "Icons";
            fileTags: "qt.core.resource_data";
            files: [
                "res/refresh-cw.svg",
                "res/save.svg",
                "res/folder.svg",
                "res/eye-off.svg",
            ]
        }

    }
}
