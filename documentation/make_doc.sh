cd $(dirname "$0")
rm -f refman.pdf
doxygen doxygen.conf
cd latex
make
mv refman.pdf ..
cd ..
rm -rfd latex