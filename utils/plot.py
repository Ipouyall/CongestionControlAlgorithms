import argparse
import pandas as pd
import matplotlib.pyplot as plt


def plot(file, title, show):
    df = pd.read_csv(file, header=None)
    x = df[0]
    y = df[1]

    plt.plot(x, y)

    plt.xlabel('Time(RTT)')
    plt.ylabel('Congestion Window(cwnd)')
    plt.title(title)
    plt.savefig(file[:-4] + '.png')
    if show:
        plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Plot data from a CSV file')
    parser.add_argument('csv_file', type=str, help='Path to the CSV file')
    parser.add_argument('title', type=str, help='Title for the plot')
    parser.add_argument('show', type=bool, default=False,
                        help='Specify whether to display the plot (True) or not (False)')

    args = parser.parse_args()

    plot(args.csv_file, args.title, args.show)
