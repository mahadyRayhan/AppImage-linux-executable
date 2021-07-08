cmake_minimum_required(VERSION 3.0)

project(QTAppImage-hello-world)

file(GLOB SOURCES
            "*.h"
            "*.cpp"
            "*.cc"
            "Classes/*/*.cpp"
            "Classes/*/*.h"
            "src/*.h"
            "src/*.cpp"
            "src/*.cc"
            "src/Classes/*/*.cpp"
            "src/Classes/*/*.h"
            "res/*.desktop"
            "res/*.png"
    )

# import Qt libraries
find_package(Qt5 REQUIRED COMPONENTS Quick Gui Qml)

# find includes in current build dir (required for MOC)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# run Qt's MOC automatically if required
set(CMAKE_AUTOMOC ON)
# create code for given designer UI files
set(CMAKE_AUTOUIC ON)
# compile resources automatically using rcc
set(CMAKE_AUTORCC ON)

# make information from Qt resource file available in CMake
qt5_add_resources(QT_RESOURCES ./src/qml.qrc)

# build binary from C++ code and the imported Qt resource data
add_executable(QTAppImage-hello-world ./src/main.cpp ${QT_RESOURCES} ${SOURCES})
# link to Qt5 libraries
target_link_libraries(QTAppImage-hello-world Qt5::Quick Qt5::Gui Qt5::Qml)

# install QTAppImage-hello-world binary
install(
    TARGETS QTAppImage-hello-world
    RUNTIME DESTINATION bin
)

install(
    FILES ./res/QTAppImage-hello-world.desktop
    DESTINATION share/applications/
)

install(
    FILES ./res/QTAppImage-hello-world.png
    DESTINATION share/icons/hicolor/128x128/apps
)
