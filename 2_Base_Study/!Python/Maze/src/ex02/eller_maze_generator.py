import random
import numpy as np


class EllerMazeGenerator:
    """Class to generate a perfect maze using Eller's algorithm."""

    def __init__(self, n_rows, n_cols):
        self.n_rows = n_rows
        self.n_cols = n_cols
        self.vertical_walls = np.ones((n_rows, n_cols), dtype=int)
        self.horizontal_walls = np.ones((n_rows, n_cols), dtype=int)
        self.sets = [i for i in range(n_cols)]

    def generate_maze(self):
        """Generate the maze using Eller's algorithm."""
        for row in range(self.n_rows - 1):
            self.join_right(row)
            self.join_down(row)
            self.prepare_next_row(row)

        self.join_right(self.n_rows - 1, force_join=True)
        self.save_maze_to_file("generated_maze.txt")

        return self.vertical_walls, self.horizontal_walls

    def join_right(self, row, force_join=False):
        """Randomly join cells horizontally."""
        for col in range(self.n_cols - 1):
            if force_join or random.choice([True, False]):
                if self.sets[col] != self.sets[col + 1]:
                    self.vertical_walls[row, col] = 0
                    self.union_sets(self.sets[col], self.sets[col + 1])

    def join_down(self, row):
        """Randomly join cells vertically."""
        new_set = [-1] * self.n_cols
        for col in range(self.n_cols):
            if (row == self.n_rows - 2 or random.choice([True, False])) and self.count_cells_in_set(self.sets[col], new_set) > 1:
                self.horizontal_walls[row, col] = 0
                new_set[col] = self.sets[col]
            else:
                new_set[col] = self.create_new_set()

        self.sets = new_set

    def prepare_next_row(self, row):
        """Prepare the sets for the next row."""
        for col in range(self.n_cols):
            if self.horizontal_walls[row, col] == 1:
                self.sets[col] = self.create_new_set()

    def create_new_set(self):
        """Create a new unique set id."""
        return max(self.sets) + 1

    def count_cells_in_set(self, set_id, new_set):
        """Count how many cells are in a given set."""
        return sum(1 for cell in new_set if cell == set_id)

    def union_sets(self, set1, set2):
        """Union two sets."""
        for idx, val in enumerate(self.sets):
            if val == set2:
                self.sets[idx] = set1

    def save_maze_to_file(self, file_name):
        """Save the maze to a file."""
        with open(file_name, 'w') as file:
            file.write(f"{self.n_rows} {self.n_cols}\n")
            for row in self.vertical_walls:
                file.write(" ".join(map(str, row)) + "\n")
            for row in self.horizontal_walls:
                file.write(" ".join(map(str, row)) + "\n")
