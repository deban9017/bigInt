# Modify this file to implement the count_pairs_file function
# using ultra-large integers in C/C++.

import ctypes


def read_file(filename: str) -> tuple[list[int], int]:
    with open(filename) as file:
        # First line is the target
        target = int(file.readline())
        # Second line is the number of integers
        n = int(file.readline())
        # Read the n integers and return them as a list
        return ([int(file.readline()) for _ in range(n)], target)
    
def read_file_C(filename: str) -> tuple[list[int], int, int]:
    with open(filename) as file:
        # First line is the target
        target = str(file.readline())
        # Second line is the number of integers
        n = int(file.readline())
        # Read the n integers and return them as a list
        return ([str(file.readline()) for _ in range(n)], target, n)


def count_pairs(data: list[int], target: int) -> int:
    """Count the number of pairs of
    list indices i < j such that
    data[i] - data[j] = target.
    Time complexity: Naive O(n^2).
    """
    result = 0
    n = len(data)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if data[i] - data[j] == target:
                result += 1
    return result


def test_count_pairs():
    # Simple correctness tests
    assert count_pairs([1, 2, 3, 4, 5], 1) == 0
    assert count_pairs([5, 4, 3, 2, 1], 1) == 4
    assert count_pairs([1, 2, 3, 4, 5], -3) == 2
    # Test with huge integers
    assert count_pairs([10**20 + 2, 10**20 + 1, 10**20], 1) == 2
    print("count_pairs.py: All tests passed")


def count_pairs_file_py(filename: str) -> int:
    data, target = read_file(filename)
    return count_pairs(data, target)



def python_list_to_c_char_pp(string_list):
    # Create a C array of pointers to char
    CCHARP = ctypes.POINTER(ctypes.c_void_p)
    char_pp = (ctypes.c_char_p * len(string_list))()
    for i, s in enumerate(string_list):
        char_pp[i] = ctypes.c_char_p(s.encode('utf-8'))

    return char_pp



def count_pairs_file(filename: str) -> int:
    # try:
    UltraIntLib = ctypes.CDLL("./UltraIntLib.so")
    # except:
    #     UltraIntLib = ctypes.CDLL("./UltraIntLib.dll")
    count_pairs_c = UltraIntLib.count_pairs
    # int count_pairs(void * arr, char* targetStr, int numsLen);
    count_pairs_c.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
    count_pairs_c.restype = ctypes.c_int
    
    # Read the file
    data, target, n = read_file_C(filename)
    
    # we need to pass the list data[str] to C as a void pointer, we would typecast it to a char** in C
    char_p = ctypes.c_char_p(target.encode('utf-8'))
    len = ctypes.c_int(n)
    char_pp = python_list_to_c_char_pp(data)


    return count_pairs_c(char_pp, char_p, len)




