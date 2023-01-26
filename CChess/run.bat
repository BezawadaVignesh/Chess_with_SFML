@set SFML_DIR=C:\Users\vigne\OneDrive\Documents\vignesh\CSFML-2.5.1
mkdir build
cd build
C:\MinGW\mingw64\bin\gcc  -c %CD%\..\main.c %CD%\..\vector.c -I%SFML_DIR%\include -DSFML_STATIC
C:\MinGW\mingw64\bin\gcc -o %CD%\main %CD%\main.o %CD%\vector.o -L%SFML_DIR%\lib\gcc -lcsfml-audio -lcsfml-graphics -lcsfml-window -lcsfml-system
%CD%\main
cd..
