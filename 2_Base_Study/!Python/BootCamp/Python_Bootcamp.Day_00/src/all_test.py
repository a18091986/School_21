# def test_blocks():
#     with open('for_tests/ex01/data_hashes_10lines.txt', 'r') as f:
#         line = f.readline().strip()
#         while line:
#             print(line)
#             line = f.readline().strip()
#
#
# if __name__ == 'main':
#     test_blocks()


import subprocess
command = r"type for_tests/ex01/data_hashes_10lines.txt | python blocks.py 20"

result = subprocess.run(command, capture_output=True, text=True, shell=True)
print(result)
print(result.stdout)