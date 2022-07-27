cmake_minimum_required(VERSION 3.10)

# set the project name
project(Npc)

# add the executable
file(GLOB SRC ../src/*.c)
add_executable(npc ${SRC})