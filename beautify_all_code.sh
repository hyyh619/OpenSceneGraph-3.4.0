find . -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.m" > source.files 
uncrustify -c ../../tools/hy_c_c++_for_osx.cfg -F source.files --no-backup
