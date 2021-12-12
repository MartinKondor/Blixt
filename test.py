"""
Testing Blixt's compressing abilites.
"""
import os
import random


print('Blixt tester.')

# Make sure the executable exists
if not os.path.exists('bin/blx.o'):
    print('Cannot find "blx.o" file.')
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
os.system('bin/blx.o bin/test.txt')

# Load compressed data
compressed_data = ""
try:
    with open('bin/test.txt.blx', 'r') as file:
        compressed_data = file.read()
except:
    print()
    print("No compressed file found, test stops.")
    exit(0)

print()
print('Size comparision')
print('=======')
print('Original size: \t\t\t{} byte'.format(len(test_data)))
print('Compressed size: \t\t{} byte'.format(len(compressed_data)))
print('Compression effectiveness: \t{}%'.format(100 - len(compressed_data) / (len(test_data) / 100)))
print()

# Testing decompression
os.system("./bin/blx.o test.txt.blx test.ublx.txt")

# Load decompressed data
decompressed_data = None
with open('bin/test.txt', 'r') as file:
    decompressed_data = file.read()

print()
print('Accuracy test')
print('=======')
#print('{}% accurate'.format(100 * len(decompressed_data) / [decompressed_data[i] == test_data[i] for i in range(len(decompressed_data))].count(True)))

n_correct = 0
test_data = [_.strip() for _ in test_data.splitlines() if _]
decompressed_data = [_.strip() for _ in decompressed_data.splitlines() if _]

for d1, d2 in zip(test_data, decompressed_data):
    if d1 == d2:
        n_correct += 1
    else:
        print("[CERROR] d1 =", d1, "but d2 =", d2)

print(100 * len(decompressed_data) / n_correct, '%')

