./std m > a
./ft m > b;
echo "\033[1;33mMAP :"
diff -y --suppress-common-lines a b > result && echo "\033[1;32m  SUCCESS\033[0m" || echo "\033[1;31m  FAILURE\033[0m, executing 'cat result'"
diff -y --suppress-common-lines a b || diff -y a b
rm -rf result
rm -rf a b
echo "\033[1;33mSTACK :"
./std s > a
./ft s > b;
diff -y --suppress-common-lines a b > result && echo "\033[1;32m  SUCCESS\033[0m" || echo "\033[1;31m  FAILURE\033[0m, executing 'cat result'"
diff -y --suppress-common-lines a b || diff -y a b
rm -rf result
rm -rf a b
echo "\033[1;33mVECTOR :"
./std v > a
./ft v > b;
diff -y --suppress-common-lines a b > result && echo "\033[1;32m  SUCCESS\033[0m" || echo "\033[1;31m  FAILURE\033[0m, executing 'cat result'"
diff -y --suppress-common-lines a b || diff -y a b
rm -rf result
rm -rf a b