import tsp
import numpy as np
import random
import math

def nearest_neighbor(prob, **_):
    # Begin path at a random point
    remaining = list(range(prob.dim))
    prev = remaining.pop(random.randint(0, prob.dim-1))
    path = np.zeros(prob.dim, dtype=np.int_)
    path[0] = prev
    weight = 0

    for i in range(1, prob.dim):
        # Pick nearest neighbor
        best = math.inf
        for point in remaining:
            score = prob.edge_weight((prev, point))
            if score < best:
                nearest = point
                best = score

        # Add nearest neighbor to path
        remaining.remove(nearest)
        path[i] = nearest
        weight += best
        prev = nearest

    # Add weight of last edge and return
    weight += prob.edge_weight((prev, path[0]))
    return tsp.Tour(path), weight

def hill_climbing(prob, **_):
    # Generate a random starting tour
    tour = tsp.Tour(np.arange(prob.dim))
    random.shuffle(tour.arr)
    weight = prob.tour_weight(tour)

    key_func = lambda op: op.weight_diff(tour, prob)

    while True:
        best_op = min(tsp.TwoOpt.list_all(prob.dim), key=key_func)
        best_diff = best_op.weight_diff(tour, prob)

        if best_diff == 0:
            return tour, weight

        best_op.apply(tour)
        weight += best_diff

def simulated_annealing(prob, c=0.0005, temp=None, iters=50000, **kwargs):
    # Data for debugging / tuning parameters
    data = np.zeros((iters, 2))

    # Generate a random starting tour
    tour = tsp.Tour(np.arange(prob.dim))
    random.shuffle(tour.arr)
    weight = prob.tour_weight(tour)

    if temp is None:
        temp = weight

    for i in range(iters):
        temp *= 1-c
        op = tsp.TwoOpt.random(prob.dim)
        diff = op.weight_diff(tour, prob)
        if diff < 0 or random.random() < pow(math.e, -diff/temp):
            weight += diff
            op.apply(tour)
        data[i] = [temp, weight]

    return tour, weight, data[:,0], data[:,1]

def ant_colony(prob, iters=1500, p=0.005, q=None, **kwargs):
    if q is None:
        q = prob.average_tour_weight() / 100

    # Data for debugging / tuning parameters
    data = np.zeros((iters, 3))

    best = math.inf
    trail = np.ones((prob.dim, prob.dim))
    for iter in range(iters):
        # Begin path at random point
        remaining = list(range(prob.dim))
        prev = remaining.pop(random.randint(0, prob.dim-1))
        path = np.zeros(prob.dim, dtype=np.int_)
        path[0] = prev
        weight = 0

        # Traverse graph
        for i in range(1, prob.dim):
            # Pick random neighbor
            pweights = [trail[prev,edge]/prob.edge_weight((prev,edge)) for edge in remaining]
            neighbor = random.choices(remaining, pweights)[0]
            remaining.remove(neighbor)

            # Add neighbor to path
            path[i] = neighbor
            weight += prob.edge_weight((prev, neighbor))
            prev = neighbor

        weight += prob.edge_weight((prev, path[0]))

        # Update trails
        trail *= 1-p
        for i, j in zip(path, np.roll(path, 1)):
            trail[i,j] += q/weight
            trail[j,i] += q/weight

        # Update best
        if weight < best:
            best_tour = path

        data[iter] = [np.min(trail), np.max(trail), weight]

    return tsp.Tour(best_tour), weight, data[:,0], data[:,1], data[:,2]
