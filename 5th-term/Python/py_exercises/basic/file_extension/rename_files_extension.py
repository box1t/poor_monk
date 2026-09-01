# Write a Python script to rename all files in a folder by changing their extensions.
from pathlib import Path

def rename_files_extension(directory, old_ext, new_ext):
    """
    Renames all files in a directory by changing their extension.
    """
    # 1. Ensure extensions start with a dot
    if not old_ext.startswith('.'):
        old_ext = '.' + old_ext
    if not new_ext.startswith('.'):
        new_ext = '.' + new_ext
    
    # 2. Create a Path object for the directory
    folder = Path(directory)
    
    # 3. Check if the directory exists
    if not folder.exists():
        print(f"Error: Directory '{directory}' does not exist.")
        return
    
    if not folder.is_dir():
        print(f"Error: '{directory}' is not a directory.")
        return
    
    # 4. Find all files with the old extension
    files_to_rename = [f for f in folder.glob(f"*{old_ext}") if f.is_file()]
    
    if not files_to_rename:
        print(f"No files with extension '{old_ext}' found in '{directory}'.")
        return
    
    # 5. Show what will be renamed (dry run)
    print(f"Found {len(files_to_rename)} file(s) to rename:\n")
    renamed_count = 0
    
    for file in files_to_rename:
        # .with_suffix() creates a new Path with a different extension
        new_path = file.with_suffix(new_ext)
        
        # Safety check: don't overwrite existing files
        if new_path.exists():
            print(f"  [SKIPPED] {file.name} -> {new_path.name} (target already exists)")
            continue
        
        # Perform the rename
        file.rename(new_path)
        print(f"  [RENAMED] {file.name} -> {new_path.name}")
        renamed_count += 1
    
    print(f"\nDone! {renamed_count} file(s) renamed successfully.")

# --- Example usage ---
if __name__ == "__main__":
    # Change these values to match your needs
    target_directory = "./my_folder"
    old_extension = "txt"
    new_extension = "md"
    
    print(f"Renaming *.{old_extension} files to *.{new_extension} in '{target_directory}'...\n")
    rename_files_extension(target_directory, old_extension, new_extension)