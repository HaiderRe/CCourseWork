g++ tile_map_testing_testing.cpp include/AStar.cpp -o tile_map_testing_testing.exe -O1 -Wall -std=c++17 -w -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
start-sleep 0.5
start-process tile_map_testing_testing.exe
