cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

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
)
