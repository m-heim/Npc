cmake_minimum_required(VERSION 3.10)

# set the project name
project(Npc)
include(CTest)

# add the executable
file(GLOB SRC ./*.c)
add_executable(npc ${SRC})
add_test(NAME run COMMAND npc ../programs/test_program.npc)