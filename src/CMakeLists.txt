cmake_minimum_required(VERSION 3.10)

# set the project name
project(Npc)
include(CTest)

# add the executable
file(GLOB SRC ./*.c)
add_executable(npc ${SRC})
add_test(NAME run1 COMMAND npc ../programs/simple_test_program.npc)
add_test(NAME run2 COMMAND npc ../programs/expression_test_program.npc)
add_test(NAME run3 COMMAND npc ../programs/complex_test_program.npc)