$PWD = pwd
doxygen documentation/npc.doxy
cd latex
make
mv $PWD/documentation/latex/refman.pdf $PWD/documentation
rm -rfd html latex
cd $PWD