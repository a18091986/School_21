import numpy as np


class Maze:
    """Class to represent a maze with walls."""

    def __init__(self, n_rows, n_cols, vertical_walls, horizontal_walls):
        self.n_rows = n_rows
        self.n_cols = n_cols
        self.vertical_walls = np.array(vertical_walls)
        self.horizontal_walls = np.array(horizontal_walls)

    @staticmethod
    def load_from_file(file_path):
        """Loads a maze from a file and returns a Maze object."""
        with open(file_path, 'r') as file:
            lines = file.readlines()

        n_rows, n_cols = map(int, lines[0].strip().split())
        vertical_walls = [list(map(int, line.strip().split())) for line in lines[1:n_rows + 1]]
        horizontal_walls = [list(map(int, line.strip().split())) for line in lines[n_rows + 1:]]

        return Maze(n_rows, n_cols, vertical_walls, horizontal_walls)
