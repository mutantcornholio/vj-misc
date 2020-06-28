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
            "src/commons.cpp",
            "src/commons.h",
            "src/defines.cpp",
            "src/initApp.cpp",
            "src/initApp.h",
            "src/main.cpp",
            "src/ui/MainWindow/mainwindow.cpp",
            "src/ui/MainWindow/mainwindow.h",
            "src/ui/MainWindow/mainwindow.ui",
            "src/files/PresetContent/presetcontent.cpp",
            "src/files/PresetContent/presetcontent.h",
            "src/QSyphonServer/qsyphonserver.h",
            "src/QSyphonServer/qsyphonserver.mm",
            "src/ui/TextGLWidget/textglwidget.cpp",
            "src/ui/TextGLWidget/textglwidget.h",
            "src/ui/FontTuner/fonttuner.cpp",
            "src/ui/FontTuner/fonttuner.h",
            "src/ui/FontTuner/fonttuner.ui",
            "src/ui/StatusSender/statussender.h",
            "src/ui/StatusSender/statussender.cpp",
            "src/ui/VJTextDocument/vjtextdocument.cpp",
            "src/ui/VJTextDocument/vjtextdocument.h",
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
        Group {
            name: "Icons";
            fileTags: "qt.core.resource_data";
            files: [
                "res/refresh-cw.svg",
                "res/save.svg",
                "res/folder.svg",
            ]
        }

    }
}
