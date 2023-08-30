import os
import fnmatch

def count_lines(filename):
    with open(filename, 'r') as f:
        return len(f.readlines())

def find_files(directory, pattern, ignore_list):
    for root, dirs, files in os.walk(directory):
        for basename in files:
            if fnmatch.fnmatch(basename, pattern) and basename not in ignore_list:
                filename = os.path.join(root, basename)
                yield filename

def main():
    directory = 'C:/Users/HaiderTheBot/Documents/GitHub/CCourseWork/learning'
    patterns = ['*.hpp', '*.cpp']
    ignore_list = ["rlgl.h", "raylib.h", "raymath.h", "rapidxml.hpp", 
                   "rapidxml_iterators.hpp", "rapidxml_print.hpp", 
                   "rapidxml_utils.hpp", "json.hpp", "aStar.hpp", "dyn_mem_acc.cpp", 
                   "main.cpp", "ping_pong.cpp", "short_if.cpp", "testing_cin_clear.cpp", "AStar.cpp"]
    total_lines = 0
    file_line_counts = []  # List to store (filename, line_count) tuples

    for pattern in patterns:
        for filename in find_files(directory, pattern, ignore_list):
            line_count = count_lines(filename)
            total_lines += line_count
            file_line_counts.append((filename, line_count))
            
    # Sort the list of (filename, line_count) tuples by line_count in descending order
    sorted_file_line_counts = sorted(file_line_counts, key=lambda x: x[1], reverse=True)
    
    # Print the sorted results
    for filename, line_count in sorted_file_line_counts:
        print(f"{filename}: {line_count} lines")
        
    print(f'Total lines of code in all .hpp and .cpp files (ignoring certain files): {total_lines}')

if __name__ == '__main__':
    main()
