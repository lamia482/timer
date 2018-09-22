set -e
clear
rm -f core
ulimit -c unlimited
echo "*** START ***"
./gen $1 $2 $3 $4
echo "***  END  ***"
