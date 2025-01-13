cmake_minimum_required(VERSION 3.30)
project(ProjetoEDOO)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjetoEDOO main.cpp
        produto.h produto.cpp
        pedido.h pedido.cpp
        prato.h prato.cpp
        json.hpp
        restaurante.cpp
        restaurante.h
)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

target_link_libraries(ProjetoEDOO PRIVATE nlohmann_json::nlohmann_json)
