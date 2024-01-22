cmake_minimum_required(VERSION 3.16)

project(journalviewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Boost REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED libsystemd)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appjournalviewer
    main.cpp
)

qt_add_qml_module(appjournalviewer
    URI journalviewer
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES JournalGrid.qml
    QML_FILES NavigationMenu.qml
    SOURCES journalinterface.h journalinterface.cpp
    SOURCES journalmodel.h journalmodel.cpp
    SOURCES navmodel.h navmodel.cpp
    SOURCES journalfields.h journalfields.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appjournalviewer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appjournalviewer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appjournalviewer
    PRIVATE Qt6::Quick
    PRIVATE systemd
)

include(GNUInstallDirs)
install(TARGETS appjournalviewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
