qt_add_library(MainWindowModule STATIC)

qt_add_qml_module(MainWindowModule
    URI QBATask.MainWindow
    VERSION 1.0
    RESOURCE_PREFIX /qml
    QML_FILES
        main.qml
        SenderDialog.qml
        ReceiverDialog.qml
        CanDialog.qml
        DriveShapes.qml
        UdpSocketList.qml
    RESOURCES
         ../images/felif.png
         ../doc/test.xml
    NO_PLUGIN
)
