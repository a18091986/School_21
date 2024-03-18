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
import pytest
import subprocess


def test_1_blocks():
    command = r"cat for_tests/ex01/1.txt | python blocks.py 20"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    correct = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
0000071f49cffeaea4184be3d507086v
В поданном на вход файле меньше строк, чем было указано, завершение программы
"""
    assert result.stdout == correct

def test_2_blocks():
    command = r"cat for_tests/ex01/1.txt | python blocks.py"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    correct = """Incorrect command line arg
"""
    assert result.stdout == correct

def test_3_blocks():
    command = r"cat for_tests/ex01/1.txt | python blocks.py 10"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    correct = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
0000071f49cffeaea4184be3d507086v
"""
    assert result.stdout == correct

def test_4_blocks():
    command = r"cat for_tests/ex01/2.txt | python blocks.py 12"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    correct = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
0000071f49cffeaea4184be3d507086v
"""
    assert result.stdout == correct

def test_5_blocks():
    command = r"cat for_tests/ex01/2.txt | python blocks.py 10"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    correct = """00000254b208c0f43409d8dc00439896
0000085a34260d1c84e89865c210ceb4
"""
    assert result.stdout == correct

def test_1_decypher():
    with open ('for_tests/ex02/1.txt', 'r') as f:
        text = f.read()
    command = f"python3 decypher.py '{text}'"
    correct = "towerbridge\n"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    assert result.stdout == correct

def test_2_decypher():
    with open ('for_tests/ex02/2.txt', 'r') as f:
        text = f.read()
    command = f"python3 decypher.py '{text}'"
    correct = "bigben\n"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    assert result.stdout == correct

def test_3_decypher():
    with open ('for_tests/ex02/3.txt', 'r') as f:
        text = f.read()
    command = f"python3 decypher.py '{text}'"
    correct = "hydepark\n"
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    assert result.stdout == correct

def test_mfinder_1():
     for text, correct in [('1.txt', 'True\n'), 
                           ('2.txt', 'False\n'), 
                           ('3.txt', 'False\n'), 
                           ('4.txt', 'False\n'), 
                           ('5.txt', 'False\n'), 
                           ('6.txt', 'False\n'),
                           ('7.txt', 'True\n')
                           ]:
         command = rf"cat for_tests/ex03/{text} | python mfinder.py"
         result = subprocess.run(command, capture_output=True, text=True, shell=True)
         assert result.stdout == correct
