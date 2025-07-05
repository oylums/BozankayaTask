cmake_minimum_required(VERSION 3.16)

project(QBATask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Xml REQUIRED)

qt_add_resources(RESOURCES  qbataskresources.qrc)

qt_add_executable(appQBATask
    main.cpp
    Application.hpp Application.cpp
    QmlGlobal.hpp   QmlGlobal.cpp
    UdpController.hpp UdpController.cpp
    XmlController.hpp XmlController.cpp
    UdpSender.hpp UdpSender.cpp
    UdpReceiver.hpp UdpReceiver.cpp
)

add_subdirectory(ui)

target_link_libraries(appQBATask
    PRIVATE
    MainWindowModule
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQBATask PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQBATask
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQBATask
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::Xml
)

include(GNUInstallDirs)
install(TARGETS appQBATask
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
