# https://en.wikipedia.org/wiki/Monty_Hall_problem


import numpy as np
import matplotlib.pyplot as plt
import random


def main():
    ports = [0, 1, 2]
    total_simulations = 1000
    steps_per_simulation = 10
    win_ratio = []
    games = []

    for n in np.arange(1, total_simulations + 1, steps_per_simulation):
        wins = 0 
        for i in range(n):
            car_port = random.choice(ports)
            selected_port = random.choice(ports)
            if selected_port != car_port:
                wins += 1  # trade & win
        win_ratio.append(wins / n)    
        games.append(n)
                
    plt.plot(games, win_ratio, 'ro-', label='Percentual de vitórias simuladas ao trocar de porta')
    plt.axhline(y=2/3, color='blue', label='Probabilidade teórica de vitória ao trocar de porta')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
