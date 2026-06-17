cmake_minimum_required(VERSION 3.16)

project(StudentGradeManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic compilation of Qt files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 components
find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    addstudentdialog.cpp
    chartsview.cpp
    student.h
    mainwindow.h
    addstudentdialog.h
    chartsview.h
    resources.qrc
)

# Executable target
add_executable(StudentGradeManager ${SOURCES})

# Target links
target_link_libraries(StudentGradeManager PRIVATE
    Qt6::Widgets
    Qt6::Charts
)

# Desktop entry integration and install rules (helpful for deb packaging)
install(TARGETS StudentGradeManager RUNTIME DESTINATION bin)
