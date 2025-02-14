# NOTHINg in this file should be modified

from count_pairs import count_pairs_file_py
from count_pairs import count_pairs_file
import sys
import time

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f'Run {sys.argv[0]} with arguments <filename>')
        sys.exit(1)
    # Open the file argv[1]
    filename = sys.argv[1]
    # Call count_pairs_file and print the result
    start = time.time()
    py = count_pairs_file_py(filename)
    pytime = time.time() - start
    start = time.time()
    c = count_pairs_file(filename)
    ctime = time.time() - start
    print("Python :", py)
    print("Python time:", pytime)
    print("C :", c)
    print("C time:", ctime)