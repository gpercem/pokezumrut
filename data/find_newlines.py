import os
import re

def read_file(filename):
  """Reads a file and returns its contents as a string."""
  with open(filename, "r", encoding="utf-8") as f:
    return f.read()

def remove_all_except(string, allowed_strings):
  pattern = '|'.join(map(re.escape, allowed_strings))
  result = re.findall(pattern, string)
  return ''.join(result)

def check_for_repeated_newlines(string):
  if "\\n\\n" in string:
    print(string)
    return True
  else:
    return False

def main():
  """The main function."""

  # Get the map folder from the user
  map_folder = input("Enter the map folder to search: ")

  # Iterate over all the scripts.inc files in the map folder
  for root, dirs, files in os.walk(map_folder):
    for file in files:
      if file == "scripts.inc":
        # Read the contents of the scripts.inc file
        scripts_inc_contents = read_file(os.path.join(root, file))

        # Remove all strings except for "zzu", "\n", "\l", and "$" from the scripts.inc file
        temp_variable = remove_all_except(scripts_inc_contents, ["\\p", "\\n", "\\l", "$"])

        # Check if the temp variable contains any repeated newline characters
        if check_for_repeated_newlines(temp_variable):
          # Print the directory location of the scripts.inc file
          print("Found repeated newlines in scripts.inc file:", os.path.join(root, file),"\n\n")

if __name__ == "__main__":
  main()
