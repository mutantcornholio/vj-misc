import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile

//import "/Applications/of_v0.10.1_osx_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "/Applications/of_v0.10.1_osx_release"
//    property bool makeOF: true
//    property bool precompileOfMain: false

    QtGuiApplication {

        name: "vj-misc"

        files: [
            "defines.cpp",
            "main.cpp",
            "mainwindow.cpp",
            "mainwindow.h",
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

        Depends {
            name: "Qt"
            submodules: ["core", "gui", "widgets"] // Add more here if needed
        }

        // dependency with the OF library
//        Depends{
//            name: "openFrameworks"
//        }
    }
    //references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}


//    QtGuiApplication {
//        name: "vj-misc"

//        files: [
//            "main.cpp",
//            "mainwindow.cpp",
//            "mainwindow.h",
//            "textglwidget.cpp",
//            "textglwidget.h",
//            "mainwindow.ui",
//            "fonttuner.cpp",
//            "fonttuner.h",
//            "fonttuner.ui",
//        ]

//        cpp.frameworks: ["opengl"]
//        cpp.includePaths: [product.sourceDirectory]

//        Depends {
//            name: "Qt"
//            submodules: ["core", "gui", "widgets"] // Add more here if needed
//        }

//        // common rules that parse the include search paths, core libraries...
//        Depends{
//            name: "of"
//        }

//        // dependency with the OF library
//        Depends{
//            name: "openFrameworks"
//        }
//    }
