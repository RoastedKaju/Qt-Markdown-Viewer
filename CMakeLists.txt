cmake_minimum_required(VERSION 3.24)

project(Qt-Markdown-Viewer LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    cmark
    GIT_REPOSITORY https://github.com/commonmark/cmark.git
    GIT_TAG 0.31.1)

FetchContent_MakeAvailable(cmark)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Qt-Markdown-Viewer
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(Qt-Markdown-Viewer
    PRIVATE
        Qt::Core
        Qt::Widgets
        cmark
)

include(GNUInstallDirs)

install(TARGETS Qt-Markdown-Viewer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Qt-Markdown-Viewer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
