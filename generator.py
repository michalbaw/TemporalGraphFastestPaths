#!/bin/python3

# For now, only Contact Sequence Temporal Graphs can be generated.

from sys import stdin, argv
import numpy
import random

temporal_per_edge = int(argv[1])
timespan = int(argv[2])
avg_edge_length = int(argv[3])
question_count = int(argv[4])

def get_rand_edgecount ():
    global temporal_per_edge
    return max(round(numpy.random.normal(temporal_per_edge, temporal_per_edge/3)), 1)

def get_rand_edge_begin ():
    global timespan
    return random.randint(0, timespan)

def get_rand_edge_length ():
    global avg_edge_length
    return random.randint(1, avg_edge_length*2)

graph = []

n = 0
m = 0

def get_rand_vertex ():
    global n
    return random.randint(0, n)

for line in stdin:
    line = line.split()
    if line[0] == '%':
        continue
    a = int(line[0])
    b = int(line[1])
    a -= 1
    b -= 1
    n = max(n, a, b)
    for _ in range(get_rand_edgecount()):
        m += 1
        graph.append(f'{a} {b} {get_rand_edge_begin()} {get_rand_edge_length()}')

n += 1

print(n, m, question_count)
for i in graph:
    print(i)

for _ in range(question_count):
    print(f'{get_rand_vertex()}')