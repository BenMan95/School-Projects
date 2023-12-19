import numpy as np
import itertools
import math
import random

def load_tsp(filename):
    with open(filename, 'r') as f:
        dim = None

        # Read until NODE_COORD_SECTION
        while True:
            line = f.readline().strip()
            if line == 'NODE_COORD_SECTION':
                break

            key, val = line.split(':')
            if key.strip() == 'DIMENSION':
                dim = int(val)

        if dim is None:
            return None

        # Read coords
        arr = np.zeros((dim, 2), dtype=np.double)
        while True:
            line = f.readline().strip()
            if line == 'EOF':
                break

            i, x, y = line.split()
            arr[int(i) - 1] = [float(x), float(y)]

        return TSP(arr)

def load_tour(filename):
    with open(filename, 'r') as f:
        dim = None

        # Read until NODE_COORD_SECTION
        while True:
            line = f.readline().strip()
            if line == 'TOUR_SECTION':
                break

            key, val = line.split(':')
            if key.strip() == 'DIMENSION':
                dim = int(val)

        if dim is None:
            return None

        # Read tour order
        arr = np.zeros(dim, dtype=np.int_)
        for i in range(dim):
            line = f.readline()
            arr[i] = int(line) - 1

        return Tour(arr)

# A class that represents a travelling salesman problem
class TSP:
    def __init__(self, points):
        self.points = points
        self.dim = len(points)

        self.weights = np.zeros((self.dim, self.dim))
        for i in range(self.dim):
            for j in range(self.dim):
                if i != j:
                    p1 = points[i]
                    p2 = points[j]
                    self.weights[i,j] = round(math.dist(p1, p2))

    # Computes the weight of a single edge
    def edge_weight(self, edge):
        i1, i2 = edge
        p1 = self.points[i1]
        p2 = self.points[i2]
        return round(math.dist(p1, p2))

    # Computes the weight of a non-cyclic path
    def path_weight(self, *points):
        pairs = itertools.pairwise(points)
        return sum(map(self.edge_weight, pairs))

    # Computes the weight of a cyclic tour
    def tour_weight(self, tour):
        pairs = zip(tour.arr, np.roll(tour.arr, 1))
        return sum(map(self.edge_weight, pairs))

    # Useful for certain algorithms
    def average_tour_weight(self):
        return self.weights.sum() / (self.dim-1)

# A class that represents a tour of the travelling salesman problem
class Tour:
    def __init__(self, arr):
        self.arr = arr

    def copy(self):
        return Tour(self.arr.copy())

    # Get the nth point
    def nth(self, n):
        return self.arr[n % len(self.arr)]

    def weight(self):
        return self.tsp.tour_weight(self)

# Performs a 2-opt transformation with edges (i1-1,i1) and (i2-1,i2)
# This is equivalent to reversing a subsection of the tour
class TwoOpt:
    def __init__(self, i, j):
        assert i < j
        self.i = i
        self.j = j

    # Picks a random 2-opt transformation for a problem of some size
    def random(dim):
        while True:
            i = random.randint(1,dim) - 1
            j = random.randint(i+1,dim)
            if i != 0 or j != dim:
                return TwoOpt(i,j)

    # Lists every possible 2-opt transformation for a problem of some size
    def list_all(dim):
        for i in range(dim):
            for j in range(i, dim):
                if i != 0 or j+1 != dim:
                    yield TwoOpt(i, j+1)

    # Determines the weight change if applied to a tour on some problem
    # Does not work if i and j correspond to the same node
    def weight_diff(self, tour, prob):
        weight = 0

        a, b, c, d = map(tour.nth, [self.i, self.i-1, self.j-1, self.j])

        # Subtract weight of removed edges
        weight -= prob.edge_weight((a, b))
        weight -= prob.edge_weight((c, d))

        # Add weight of new edges
        weight += prob.edge_weight((b, c))
        weight += prob.edge_weight((a, d))

        return weight

    def apply(self, tour):
        tour.arr[self.i:self.j] = tour.arr[self.i:self.j][::-1]