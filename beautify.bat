find . -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.m" > source.files 
..\..\..\..\tools\uncrustify-0.62.0-g5987f22-win32\uncrustify.exe -c "..\..\..\tools\hy_c_c++.cfg" --no-backup -F source.files
find ./include -name "*" > header.files
..\..\..\..\tools\uncrustify-0.62.0-g5987f22-win32\uncrustify.exe -c "..\..\..\tools\hy_c_c++.cfg" --no-backup -F header.files
