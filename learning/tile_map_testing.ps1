g++ tile_map_testing.cpp -o tile_map_testing.exe -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
start-sleep 0.5
start-process tile_map_testing.exe
