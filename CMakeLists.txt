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
    ./include/qtpexels_global.h
    ./src/ApiClient.cpp
    ./include/ApiClient.h
    ./src/Collection.cpp
    ./include/Collection.h
    ./src/CollectionsPage.cpp
    ./include/CollectionsPage.h
    ./src/FetchableResource.cpp
    ./include/FetchableResource.h
    ./src/Photo.cpp
    ./include/Photo.h
    ./src/PhotosPage.cpp
    ./include/PhotosPage.h
    ./src/ResultsPage.cpp
    ./include/ResultsPage.h
    ./src/Video.cpp
    ./include/Video.h
    ./src/VideosPage.cpp
    ./include/VideosPage.h
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(BUILD_SHARED_LIBS)
    add_library(QtPexelsLib SHARED ${libSrc})
	target_compile_definitions(QtPexelsLib PUBLIC BUILD_SHARED=1)
else()
    add_library(QtPexelsLib STATIC ${libSrc})
	target_compile_definitions(QtPexelsLib PUBLIC BUILD_SHARED=0)
endif()

target_link_libraries(QtPexelsLib PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

target_compile_definitions(QtPexelsLib PUBLIC QTPEXELS_LIB=1)



##############################
## Example app
##############################

option(BUILD_EXAMPLE "Build example app" ON)

if(BUILD_EXAMPLE)
    set(exampleSrc
        ./example/main.cpp
    )

    target_compile_definitions(QtPexelsLib INTERFACE QTPEXELS_LIB=0)
	#target_compile_definitions(QtPexelsLib INTERFACE BUILD_STATIC=1)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)    
    add_executable(QtPexelsLibExample ${exampleSrc})
    target_link_libraries(QtPexelsLibExample PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network QtPexelsLib)
endif()




