# Get the script's directory
$scriptDirectory = Split-Path $script:MyInvocation.MyCommand.Path

# Change the current directory to the script's directory
Set-Location $scriptDirectory

# Run the compilation command
& g++ tile_map_testing.cpp -o tile_map_testing.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

# Wait for a short period to ensure the exe file is ready
Start-Sleep -Seconds 0.5

# Run the created executable
Start-Process tile_map_testing.exe
