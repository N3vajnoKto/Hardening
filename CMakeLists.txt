cmake_minimum_required(VERSION 3.5)

project(Hardening VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        mainwindow.cpp
        mainwindow.h

        objects/objectbase.h
        objects/objectbase.cpp

        objects/object.h
        objects/object.cpp

        screen.h
        screen.cpp

        controller.h
        controller.cpp

        playerbase.h
        playerbase.cpp

        player.h
        player.cpp

        inventory.h
        inventory.cpp

        items/itembase.h
        items/itembase.cpp

        items/item.h
        items/item.cpp

        cell.h
        cell.cpp

        items/tool.h
        items/tool.cpp

        items/toolaxe.h
        items/toolaxe.cpp

        objects/objectaxe.h
        objects/objectaxe.cpp

        objects/toolobject.h
        objects/toolobject.cpp

        objects/droppeditemobject.h
        objects/droppeditemobject.cpp

        items/itemgroup.h
        items/itemgroup.cpp

        objects/lootableobject.h
        objects/lootableobject.cpp

        objects/tree.h
        objects/tree.cpp

        keys.h

        items.h
        objects.h

        damage.h
        damage.cpp

        items/itemwood.h
        items/itemwood.cpp

        objects/stone.h
        objects/stone.cpp

        items/itemstone.h
        items/itemstone.cpp

        items/toolpickaxe.h
        items/toolpickaxe.cpp

        objects/gameobject.h
        objects/gameobject.cpp

        objects/objectpickaxe.h
        objects/objectpickaxe.cpp

        objects/mob.h
        objects/mob.cpp

        objects/pig.h
        objects/pig.cpp

        animationmanager.h
        animationmanager.cpp

        icons.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Hardening
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Hardening APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Hardening SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Hardening
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Hardening PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Hardening PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Hardening
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Hardening)
endif()
