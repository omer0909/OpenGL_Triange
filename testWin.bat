cd ..
mkdir build-game-3d
cd build-game-3d
cmake ../game-3d -G "MinGW Makefiles"
MinGW32-make
game3d.exe
pause