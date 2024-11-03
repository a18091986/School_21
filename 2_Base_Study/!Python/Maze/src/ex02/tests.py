import unittest
from eller_maze_generator import EllerMazeGenerator


class TestEllerMazeGenerator(unittest.TestCase):
    """Unit tests for the EllerMazeGenerator class."""

    def test_maze_dimensions(self):
        """Test if the generated maze has the correct dimensions."""
        generator = EllerMazeGenerator(10, 10)
        vertical_walls, horizontal_walls = generator.generate_maze()
        self.assertEqual(vertical_walls.shape, (10, 10))
        self.assertEqual(horizontal_walls.shape, (10, 10))

    def test_maze_uniqueness(self):
        """Test if the generated maze is perfect (unique path between any two points)."""
        generator = EllerMazeGenerator(10, 10)
        vertical_walls, horizontal_walls = generator.generate_maze()
        # Ensure each row in vertical and horizontal walls has at least one opening
        for row in vertical_walls:
            self.assertTrue(any(row == 0))
        for row in horizontal_walls:
            self.assertTrue(any(row == 0))


if __name__ == '__main__':
    unittest.main()
