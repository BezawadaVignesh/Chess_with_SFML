@set SFML_DIR=C:\Users\Lokanadh\Desktop\compiler\SFML-2.5.1
mkdir build
cd build
g++ -o %CD%\main.o -c %CD%\..\main.cpp -I%SFML_DIR%\include -DSFML_STATIC
g++ -o %CD%\main %CD%\main.o -L%SFML_DIR%\lib -lsfml-audio-s -lsfml-graphics-s -lvorbisfile -lsfml-window-s  -lvorbisenc -lvorbis -lopengl32 -lopenal32 -lsfml-system-s -lwinmm -lgdi32 -lfreetype -logg -lFLAC
%CD%\main
cd..
