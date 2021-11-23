./std > a
./ft > b;
diff -y --suppress-common-lines a b > result && echo "\033[1;32mRESULT : SUCCESS\033[0m" || echo "\033[1;31mRESULT : FAILURE\033[0m, executing 'cat result'"
diff -y --suppress-common-lines a b && rm -rf result || cat result
rm -rf a b