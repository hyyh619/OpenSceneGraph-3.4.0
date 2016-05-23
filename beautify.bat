REM find . -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.m" > source.files 
..\..\..\tools\uncrustify.exe -c "..\..\..\tools\hy_c_c++.cfg" --no-backup -F source.files
REM find ./include -name "*" > header.files
REM ..\..\..\tools\uncrustify.exe -c "..\..\..\tools\hy_c_c++.cfg" --no-backup -F header.files
