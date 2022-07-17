cmake_minimum_required(VERSION 3.14)

##############################
## QtPexelsLib
##############################

project(QtPexelsLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared library" ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

set(CMAKE_DEBUG_POSTFIX d)

set(libSrc
    ./src/ApiClient.cpp
    ./src/Collection.cpp
    ./src/CollectionsPage.cpp
    ./src/FetchableResource.cpp
    ./src/Photo.cpp
    ./src/PhotosPage.cpp
    ./src/ResultsPage.cpp
    ./src/Video.cpp
    ./src/VideosPage.cpp
    ./src/ApiClientWorker.cpp
    ./include/qtpexels/qtpexels_global.h
    ./include/qtpexels/ApiClient.h
    ./include/qtpexels/Collection.h
    ./include/qtpexels/CollectionsPage.h
    ./include/qtpexels/FetchableResource.h
    ./include/qtpexels/Photo.h
    ./include/qtpexels/PhotosPage.h
    ./include/qtpexels/ResultsPage.h
    ./include/qtpexels/Video.h
    ./include/qtpexels/VideosPage.h
    ./include/qtpexels/ApiClientWorker.h
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(BUILD_SHARED_LIBS)
    add_library(QtPexelsLib SHARED ${libSrc})
    target_compile_definitions(QtPexelsLib PUBLIC BUILD_SHARED=1)
else()
    add_library(QtPexelsLib STATIC ${libSrc})
    target_compile_definitions(QtPexelsLib PUBLIC BUILD_SHARED=0)
endif()

target_include_directories(QtPexelsLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_definitions(QtPexelsLib PUBLIC QTPEXELS_LIB=1)
target_link_libraries(QtPexelsLib PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)


##############################
## Example app
##############################

option(BUILD_EXAMPLE "Build example app" ON)

if(BUILD_EXAMPLE)
    set(exampleSrc
        ./example/main.cpp
    )

    target_compile_definitions(QtPexelsLib INTERFACE QTPEXELS_LIB=0)
    # target_compile_definitions(QtPexelsLib INTERFACE BUILD_STATIC=1)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
    add_executable(QtPexelsLibExample ${exampleSrc})
    target_include_directories(QtPexelsLibExample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(QtPexelsLibExample PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network QtPexelsLib)
endif()


