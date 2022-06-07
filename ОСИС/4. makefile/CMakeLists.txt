cmake_minimum_required(VERSION 3.16)
project(C_lang C)

set(CMAKE_C_STANDARD 90)

add_executable(C_lang main.c DublyLinkedList.h Client.h ListStrings.h ClintList.h Goods.h GoodsList.h)