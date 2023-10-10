from sys import argv
from pathlib import Path
import pathlib

script_name, ex_count, day = argv
day = int(day)
cur_day = f"{day}" if day >= 10 else f"0{day}"
ex_count = int(ex_count)

for i in range(ex_count):
    ex = f"{i}" if i >= 10 else f"0{i}"
    dir = Path(Path.cwd(), "src", f"ex{ex}")
    dir.mkdir(exist_ok=True)
    Path(dir, f"day{cur_day}_ex{ex}.sql").touch(exist_ok=True)


