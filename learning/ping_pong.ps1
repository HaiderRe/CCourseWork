g++ ping_pong.cpp -o ping_pong.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
start-sleep 1.5
start-process ping_pong.exe
