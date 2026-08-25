from pathlib import PurePath

# Create a PurePath
path = PurePath("c:/Users/john/a/b/c/Documents", "file.txt")

print("Parts:", path.parts)

print("Drive:", path.drive)

print("Parent:", path.parent)

print("Name:", path.name)

path = PurePath(
    "g:/bitbucket_git_repos/personal-projects/python/pathlib_examples", "pathlib01.py"
)
print("Parts:", path.parts)
print("Drive:", path.drive)
print("Parent:", path.parent)
print("Name:", path.name)
