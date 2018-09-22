set -e
clear
make clean
make all -j8 MAIN=main.cc
echo "*** BUILD SUCCEED ***"
