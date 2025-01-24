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
        cliente.cpp
        globals.h
)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)


target_link_libraries(ProjetoEDOO PRIVATE nlohmann_json::nlohmann_json)

# =======================
# Adicionando CivetWeb
# =======================
FetchContent_Declare(
        civetweb
        GIT_REPOSITORY https://github.com/civetweb/civetweb.git
        GIT_TAG v1.16
)

FetchContent_MakeAvailable(civetweb)

# Adicionar CivetWeb como uma biblioteca estática
add_library(civetweb STATIC
        ${civetweb_SOURCE_DIR}/src/civetweb.c
)

# Definir flags de compilação para desativar funcionalidades não usadas e ativar WebSockets
target_compile_definitions(civetweb PRIVATE -DNO_CGI -DNO_SSL -DUSE_WEBSOCKET)

# Incluir diretórios do CivetWeb
target_include_directories(civetweb PUBLIC ${civetweb_SOURCE_DIR}/include)

# Linkar CivetWeb ao projeto principal
target_link_libraries(ProjetoEDOO PRIVATE civetweb ws2_32)

# Mensagem de depuração
message(STATUS "CivetWeb foi baixado para: ${civetweb_SOURCE_DIR}")