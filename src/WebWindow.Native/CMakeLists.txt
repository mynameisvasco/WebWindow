cmake_minimum_required(VERSION 3.5.0)
project(WebWindow.Native VERSION 0.1.1)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

# Includes
if(WIN32)
    include_directories(
        ${CMAKE_SOURCE_DIR} 
        ${CMAKE_SOURCE_DIR}/WebWindow.Native.Windows)
    add_definitions(-DUNICODE -D_UNICODE)
    file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/WebWindow.Native.Windows/*.cpp)
endif()
if(APPLE)
    set(CMAKE_CXX_FLAGS "-DOS_MAC")
    include_directories(${CMAKE_SOURCE_DIR})
    file(GLOB_RECURSE SRC_FILES    
        ${CMAKE_SOURCE_DIR}/WebWindow.Native.Mac/*.mm
        ${CMAKE_SOURCE_DIR}/WebWindow.Native.Mac/*.m)
endif()
if(UNIX AND NOT APPLE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    include_directories(${CMAKE_SOURCE_DIR})
    file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/WebWindow.Native.Linux/*.cpp)
endif()

add_library(WebWindow.Native SHARED ${SRC_FILES} Exports.cpp)

# Linking
if(WIN32)
find_program(NUGET_EXE NAMES nuget)
    find_library(SHLWAPI ShLwApi.lib "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64") 
    target_link_libraries(WebWindow.Native PRIVATE ${SHLWAPI})
    exec_program(${NUGET_EXE}
        ARGS install "Microsoft.Windows.ImplementationLibrary" -Version 1.0.191107.2 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
    target_link_libraries(WebWindow.Native PRIVATE ${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.ImplementationLibrary/build/native/Microsoft.Windows.ImplementationLibrary.targets)
    exec_program(${NUGET_EXE}
        ARGS install "Microsoft.Web.WebView2" -Version 0.9.579 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
    target_link_libraries(WebWindow.Native PRIVATE ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/Microsoft.Web.WebView2.targets)
endif()
if(APPLE)
    find_library(COCOA_LIB Cocoa REQUIRED)
    find_library(WEBKIT_LIB Webkit REQUIRED)
    find_library(USER_NOTIFICATIONS_LIB UserNotifications REQUIRED)
    target_link_libraries(WebWindow.Native PRIVATE ${COCOA_LIB} ${WEBKIT_LIB} ${USER_NOTIFICATIONS_LIB})
endif()
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
    pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.0)
    include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})
    target_link_libraries(WebWindow.Native PRIVATE ${GTK3_LIBRARIES} ${WEBKIT_LIBRARIES})
endif()