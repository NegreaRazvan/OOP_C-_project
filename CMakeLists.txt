cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
find_package(Qt5Widgets REQUIRED)
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.14.0\\5.14.0\\mingw73_32\\")

add_executable(untitled1 main.cpp
        Domain/Carte.cpp
        Domain/Carte.h
        Repository/Repository.cpp
        Repository/Repository.h
        Teste/Tests.cpp
        Teste/Tests.h
        Service/Service.cpp
        Service/Service.h
        UI/UI.cpp
        UI/UI.h
        UI/UI.h
        MyList/Vector.h
        MyList/Vector.h
        MyList/Vector.h
        Cos_Carti/Cos.cpp
        Cos_Carti/Cos.h
        Exception/Exception.cpp
        Exception/Exception.h
        Service/Undo.h

)
