import tsp
import searches
import timeit

import numpy as np
import matplotlib.pyplot as plt

# Checks the new_weight function of an operation on a tour
def check(tour, prob, op):
    mutated = tour.copy()
    op.apply(mutated)
    w0 = prob.tour_weight(tour)
    w1 = prob.tour_weight(mutated)
    print(f'Expected: {w1 - w0}')
    print(f'Result: {op.weight_diff(tour)}')

def plot_tour(tour, prob):
    ax = plt.gca()
    ax.set_aspect('equal', adjustable='box')

    # Plot edges
    points = prob.points[tour.arr]
    points = np.vstack((points, points[0]))
    x = points[:,0]
    y = points[:,1]
    plt.plot(x, y)

    # Plot points
    x = prob.points[:,0]
    y = prob.points[:,1]
    plt.plot(x, y, 'ko')

def test(alg, prob, optimal=None, **kwargs):
    # Time algorithm
    t0 = timeit.default_timer()
    tour, score, *data = alg(prob, **kwargs)
    t1 = timeit.default_timer()

    assert score == prob.tour_weight(tour)

    # Print output
    print(f'Time: {t1 - t0:.4f}')
    if optimal is None:
        print(f'Score: {score}')
    else:
        print(f'Score: {score} / {optimal} = {score/optimal:.4f}')

    # Display tour
    plot_tour(tour, prob)
    ax = plt.gca()
    ax.set_aspect('equal', adjustable='box')

    return data

if __name__ == '__main__':
    names = [
        'eil51',
        'berlin52',
        'ch130',
        'pcb442',
    ]

    params_sa = {
        'eil51':    {'c':0.0003, 'iters':50000},
        'berlin52': {'c':0.0003, 'iters':50000},
        'ch130':    {'c':0.0003, 'iters':100000},
        'pcb442':   {'c':0.0001, 'iters':500000},
    }

    params_ac = {
        'eil51':    {'p':0.01,  'iters':1000},
        'berlin52': {'p':0.01,  'iters':1000},
        'ch130':    {'p':0.005, 'iters':2000},
        'pcb442':   {'p':0.005, 'iters':3000},
    }

    probs = {name: tsp.load_tsp(f'dataset/{name}.tsp') for name in names}
    best_tours = {name: tsp.load_tour(f'dataset/{name}.opt.tour') for name in names}
    best_weights = {name: probs[name].tour_weight(best_tours[name]) for name in names}

    for name in names:
        prob = probs[name]
        best = best_tours[name]
        best_weight = best_weights[name]

        plt.figure(f'{name}: Optimal')
        plot_tour(best, prob)

        print(f'{name}: Nearest Neighbor')
        plt.figure(f'{name}: Nearest Neighbor')
        test(searches.nearest_neighbor, prob, best_weight)

        print(f'{name}: Hill Climbing')
        plt.figure(f'{name}: Hill Climbing')
        test(searches.hill_climbing, prob, best_weight)

        print(f'{name}: Simulated Annealing')
        plt.figure(f'{name}: Simulated Annealing')
        data = test(searches.simulated_annealing, prob, best_weight, **params_sa[name])

        # plt.figure('Temperature')
        # plt.plot(data[0], 'r')
        # plt.figure('Weight')
        # plt.plot(data[1], 'b')

        print(f'{name}: Ant Colony Optimization')
        plt.figure(f'{name}: Ant Colony Optimization')
        data = test(searches.ant_colony, prob, best_weight, **params_ac[name])

        # plt.figure('Min Trail')
        # plt.plot(data[0], 'r')
        # plt.figure('Max Trail')
        # plt.plot(data[1], 'b')
        # plt.figure('Weight')
        # plt.plot(data[2], 'g')

    plt.show()
