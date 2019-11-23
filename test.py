"""
Testing Blixt's compressing abilites.
"""
import os
import random


print('Blixt tester.')

# Make sure the executable exists
if not os.path.exists('bin/blx.exe'):
    print('Cannot find "blx.exe".')
    exit(0)

# Generate test data
test_data = []
random.seed(0)

for _ in range(100):
    test_data.append(str(random.random())[2:])
    
test_data = '\n'.join(test_data)

# Save test data
with open('bin/test.txt', 'w+') as file:
    file.write(test_data)

# Compress test data
os.system(r'.\bin\blx.exe test.txt')

# Load compressed data
compressed_data = None
with open('bin/test.txt.blx', 'r') as file:
    compressed_data = file.read()

print()
print('Size comparision')
print('=======')
print('Original size: \t\t\t', len(test_data))
print('Compressed size: \t\t', len(compressed_data))
print('Compression effectiveness: \t', '{}%'.format(int(100 - len(compressed_data) / (len(test_data) / 100))))
print()
