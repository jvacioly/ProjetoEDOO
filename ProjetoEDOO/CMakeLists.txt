cmake_minimum_required(VERSION 3.30)
project(ProjetoEDOO)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjetoEDOO main.cpp
        produto.h
        produto.cpp
        pedido.cpp
        pedido.h
        prato.cpp
        prato.h)
