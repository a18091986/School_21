import random
import numpy as np


class MazeGenerator:
    """Class to generate a perfect maze using Kruskal's algorithm."""

    def __init__(self, n_rows, n_cols):
        self.n_rows = n_rows
        self.n_cols = n_cols
        self.vertical_walls = np.ones((n_rows, n_cols), dtype=int)
        self.horizontal_walls = np.ones((n_rows, n_cols), dtype=int)
        self.sets = np.array([[i * n_cols + j for j in range(n_cols)] for i in range(n_rows)])

    def find_set(self, cell):
        """Find the set of a cell for the Kruskal's algorithm."""
        return self.sets[cell[0], cell[1]]

    def union_sets(self, cell1, cell2):
        """Union two sets in the Kruskal's algorithm."""
        set1 = self.find_set(cell1)
        set2 = self.find_set(cell2)

        if set1 != set2:
            self.sets[self.sets == set2] = set1

    def generate_maze(self):
        """Generate a perfect maze and return wall arrays."""
        walls = []

        # Add all walls between cells
        for r in range(self.n_rows):
            for c in range(self.n_cols):
                if c < self.n_cols - 1:
                    walls.append(((r, c), (r, c + 1), 'vertical'))
                if r < self.n_rows - 1:
                    walls.append(((r, c), (r + 1, c), 'horizontal'))

        random.shuffle(walls)

        for wall in walls:
            cell1, cell2, wall_type = wall
            if self.find_set(cell1) != self.find_set(cell2):
                self.union_sets(cell1, cell2)
                if wall_type == 'vertical':
                    self.vertical_walls[cell1[0], cell1[1]] = 0
                elif wall_type == 'horizontal':
                    self.horizontal_walls[cell1[0], cell1[1]] = 0

        return self.vertical_walls, self.horizontal_walls
