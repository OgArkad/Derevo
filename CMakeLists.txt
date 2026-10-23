cmake_minimum_required(VERSION 3.16)

project(Derevo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(Derevo
    main.cpp
    main.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    render.cpp
    render.h
    resources.qrc
)

target_link_libraries(Derevo PRIVATE Qt6::Widgets)

set_target_properties(Derevo PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Derevo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)