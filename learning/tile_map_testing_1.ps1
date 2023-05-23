$INCLUDE_DIR = "include/"
$LIB_DIR = "lib/"
$LIBS = "-lraylib -lopengl32 -lgdi32 -lwinmm"
$command = "g++ tile_map_testing.cpp include/xml_parser.hpp -o testing.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I $INCLUDE_DIR -L $LIB_DIR $LIBS"
g++ tile_map_testing.cpp include/xml_parser.hpp -o testing.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I $INCLUDE_DIR -L $LIB_DIR $LIBS
