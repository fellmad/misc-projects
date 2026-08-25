# http://stackoverflow.com/questions/2835559/parsing-values-from-a-json-file-in-python

import json

from pprint import pprint

with open('data.json') as data_file:
    data = json.load(data_file)

print(data['masks']['id'])
print(data['om_points'])
pprint(data)
