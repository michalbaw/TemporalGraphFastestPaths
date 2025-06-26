#!/bin/python3
from sys import argv

f1 = argv[1]
f2 = argv[2]
f3 = argv[3]
f4 = argv[4]

try:
    with open(f1, 'r') as file:
        content1 = file.read().strip()
    with open(f2, 'r') as file:
        content2 = file.read().strip()
    with open(f3, 'r') as file:
        content3 = file.read().strip()
    with open(f4, 'r') as file:
        content4 = file.read().strip()
except FileNotFoundError as e:
    print(f"File not found: {e.filename}")
    exit(1)

try:
    numbers1 = list(map(int, content1.split()))
    numbers2 = list(map(int, content2.split()))
    numbers3 = list(map(int, content3.split()))
    numbers4 = list(map(int, content4.split()))
except ValueError as e:
    print(f"Error parsing numbers: {e}")
    exit(1)

results = {
    f1: numbers1,
    f2: numbers2,
    f3: numbers3,
    f4: numbers4
}

all_same = (numbers1 == numbers2 == numbers3 == numbers4)

if all_same:
    print("All algorithms gave the same output.")
else:
    print("Algorithms gave different outputs.")
    
    # files = [f1, f2, f3, f4]
    # numbers = [numbers1, numbers2, numbers3, numbers4]
    
    # groups = {}
    # for i, (file, nums) in enumerate(zip(files, numbers)):
    #     nums_tuple = tuple(nums)  # Convert to tuple for hashing
    #     if nums_tuple not in groups:
    #         groups[nums_tuple] = []
    #     groups[nums_tuple].append(file)
    
    # for i, (nums, file_list) in enumerate(groups.items(), 1):
    #     print(f"  Group {i}: {', '.join(file_list)}")
    #     print(f"    Content: {' '.join(map(str, nums))}")