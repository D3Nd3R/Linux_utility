cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME lin_util)

project(${PROJECT_NAME})

set(SRC_FILES main.c proc_utils.c test.c)
set(HDR_FILE proc_utils.h test.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})
