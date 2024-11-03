import tkinter as tk
from tkinter import filedialog
from maze import Maze
from maze_generator import MazeGenerator


class MazeApp:
    """GUI Application to load and display mazes."""

    def __init__(self, root):
        self.root = root
        self.root.title("Maze Application")

        self.canvas = tk.Canvas(root, width=500, height=500, bg="white")
        self.canvas.pack()

        self.load_button = tk.Button(root, text="Load Maze", command=self.load_maze)
        self.load_button.pack(side=tk.LEFT)

        self.generate_button = tk.Button(root, text="Generate Maze", command=self.generate_maze)
        self.generate_button.pack(side=tk.RIGHT)

        self.maze = None

    def load_maze(self):
        """Loads a maze from a file and displays it."""
        file_path = filedialog.askopenfilename()
        if file_path:
            self.maze = Maze.load_from_file(file_path)
            self.draw_maze()

    def generate_maze(self):
        """Generates a perfect maze and displays it."""
        generator = MazeGenerator(10, 10)  # Example size
        vertical_walls, horizontal_walls = generator.generate_maze()
        self.maze = Maze(10, 10, vertical_walls, horizontal_walls)
        self.draw_maze()

    def draw_maze(self):
        """Draws the maze on the canvas."""
        if not self.maze:
            return

        self.canvas.delete("all")
        cell_size = 500 // self.maze.n_rows

        for r in range(self.maze.n_rows):
            for c in range(self.maze.n_cols):
                x1 = c * cell_size
                y1 = r * cell_size
                x2 = x1 + cell_size
                y2 = y1 + cell_size

                if c < self.maze.n_cols - 1 and self.maze.vertical_walls[r, c] == 1:
                    self.canvas.create_line(x2, y1, x2, y2, width=2)

                if r < self.maze.n_rows - 1 and self.maze.horizontal_walls[r, c] == 1:
                    self.canvas.create_line(x1, y2, x2, y2, width=2)

        # Draw border walls
        self.canvas.create_rectangle(0, 0, 500, 500, width=2)


def main():
    """Main function to run the GUI."""
    root = tk.Tk()
    app = MazeApp(root)
    root.mainloop()


if __name__ == "__main__":
    main()
