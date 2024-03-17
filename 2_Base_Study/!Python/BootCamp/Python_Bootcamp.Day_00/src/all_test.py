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
command = r"cat for_tests/ex01/data_hashes_10lines.txt | python blocks.py 20"

result = subprocess.run(command, capture_output=True, text=True, shell=True)
correct = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
0000071f49cffeaea4184be3d507086v
В поданном на вход файле меньше строк, чем было указано, завершение программы
"""
# print(result)
print(result.stdout)
print(correct)
print(result.stdout == correct)
assert(result.stdout == correct)