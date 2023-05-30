make > /dev/null &&
build/./compRes $2 $2 data/$1 | sort -nk 2 > out-files/$1 &&
awk -f "scripts/contar-palabras.awk" "data/$1" | sort -k1 -nk2 > "out-files/$1-awk" &&
diff -q "out-files/$1" "out-files/$1-awk"
make clean > /dev/null