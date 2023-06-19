import os
import json

def get_folder_structure(folder_path):
    folder_structure = {}

    for root, dirs, files in os.walk(folder_path):
        current_folder = os.path.relpath(root, folder_path)
        current_node = folder_structure
        for folder in current_folder.split(os.sep):
            current_node = current_node.setdefault(folder, {})

        for file in files:
            current_node[file] = None

    return folder_structure

def save_folder_structure_to_json(folder_structure, output_file):
    with open(output_file, 'w') as json_file:
        json.dump(folder_structure, json_file, indent=4)

# Provide the path to the current directory or any other directory
current_directory = os.getcwd()

folder_structure = get_folder_structure(current_directory)
save_folder_structure_to_json(folder_structure, 'folder_structure.json')
