cmake_minimum_required(VERSION 3.10)

# set the project name
project(Npc)

# add the executable
set(COMMON_SOURCES ast.c char_utils.c log.c node.c npc.c parser.c scanner.c symbol_table.c three_address_code.c typetable.c)
set(TARGET_SOURCES npc.c)
add_executable(npc ${COMMON_SOURCES} ${TARGET_SOURCES})