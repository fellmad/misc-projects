import os

print('file:', __file__)

head, tail = os.path.split(__file__)
print('head:', head)
print('tail:', tail)

root, ext = os.path.splitext(__file__)
print('root:', root)
print('ext:', ext)

just_the_filename, ext = os.path.splitext(tail)
print('just_the_filename:', just_the_filename)