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
                   "rapidxml_utils.hpp", "json.hpp"]
    total_lines = 0

    for pattern in patterns:
        for filename in find_files(directory, pattern, ignore_list):
            total_lines += count_lines(filename)
            
    print(f'Total lines of code in all .hpp and .cpp files (ignoring certain files): {total_lines}')

if __name__ == '__main__':
    main()

    

