#!/usr/bin/python3
# -*- coding: utf-8 -*- 

from itertools import islice
import sys

def open_text(name):
    try:
        fp = open(name)
    except:
        print('Cannot open ', name)
        sys.exit(2)

    return fp

def main():
    if len(sys.argv) < 3:
        print('Command-line arguments are missing.')
        print('Usage: python3 compare.py src1 src2')
        print('Usage: ./compare.py src1 src2')
        sys.exit(1)

    fp1 = open_text(sys.argv[1])
    fp2 = open_text(sys.argv[2])

    text1 = fp1.read().rstrip()
    text2 = fp2.read().rstrip()

    len1 = len(text1)
    len2 = len(text2)

    if len1 != len2:
        print('Length mismatches: {l1}, {l2}'.format(l1=len1, l2=len2))

    for i in range(len2):
        if text1[i] != text2[i]:
            print('{c1} != {c2} at {pos}.'.format(c1=text1[i], c2=text2[i], pos=i))
            break;
    else:
        print(sys.argv[1], "and", sys.argv[2], "match")


if __name__ == "__main__":
    main()


