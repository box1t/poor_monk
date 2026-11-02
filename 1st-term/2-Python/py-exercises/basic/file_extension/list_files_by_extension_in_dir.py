# Write a Python program that lists all files of a given extension in a specified directory.
from pathlib import Path

def list_files_by_extension(directory, extension):
    """
    Lists all files with a specific extension in a given directory.
    """
    # 1. Ensure the extension starts with a dot
    if not extension.startswith('.'):
        extension = '.' + extension
    
    # 2. Create a Path object for the directory
    folder = Path(directory)
    
    # 3. Create the search pattern (e.g., "*.txt")
    pattern = f"*{extension}"
    
    # 4. Find all matching files using .glob() and filter to include only files
    files_only = [f for f in folder.glob(pattern) if f.is_file()] 
    
    return files_only

# --- Example usage ---
directory_path = "."  # Current directory (change to your target folder)
file_extension = "py"  # Looking for .py files

print(f"Searching for *.{file_extension} files in '{directory_path}'...\n")

found_files = list_files_by_extension(directory_path, file_extension)

if found_files:
    print(f"Found {len(found_files)} file(s):")
    for file in found_files:
        print(f"  - {file.name}")  # .name gives just the filename
else:
    print("No matching files found.")
