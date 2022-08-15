[![CMake](https://github.com/m-heim/Npc/actions/workflows/cmake.yml/badge.svg)](https://github.com/m-heim/Npc/actions/workflows/cmake.yml)

*NPC*

A compiler project written in c, the language is called np (not pascal), its a weird mix between C and scripting languages.
You can find an example of code based upon the grammar under ./src/test_program.npc.

The progress has stalled since 2022 but i will maybe resume at some point.
The compiler is able to produce a tree of lexemes and a symbol table based upon a specific grammar (code).

*GOALS*

*Language goals:*
- [ ] Low level (C style)
- [ ] Simplicity (C style)
- [ ] Fast (C style)
- [ ] Useful builtins (Python style)
*Compiler goals:*
- [ ] Compiling process max. takes 100 % more than C
- [ ] Useful error messages
- [x] No external libraries
- [ ] Using selfmade lex/parse generator
- [ ] Executable process max. takes 100 % more than C
- [ ] Self hosted
- [ ] Supports Linux
- [ ] Supports Windows
- [ ] Supports ARM

*Done:*

- Documentation
- Scanner

*In progress:*
- Parser
  
*Todo:*
- Ir generation
- Code optimization
- Code generation
- (Peephole optimizations)

Any contributions in any way appreciated.

How to:
- preferred way to contribute is via vscode in windows with wsl or simply in linux. If you want to use another IDE do so as you wish though.
- the settings and extensions are provided in .vscode

Would really appreciate to see a pull request from you