#!/usr/bin/python3
import sys
import os
from enum import Enum
        
class Maze():
    class Kind(Enum):
        NONE = 0
        WALL = 1
        ROAD = 2
        STARTING = 3
        EXIT = 4
        PATH = 5

    class Direction(Enum):
        NONE = 0
        UP = 1
        RIGHT = 2
        DOWN = 3
        LEFT = 4
    
    def __init__(self, file_path, *args, **kwargs):
        self.points = []
        self.row = 0
        self.column = 0
        self.start = None
        self.exits = []
        self.path = None
        self.movement = 0
        self.length = 0

        self.read(file_path)

    def read(self, file_path):
        print(file_path)
        try:
            f = open(file_path, 'r')
        except IOError:
            print('Could not open file: {}'.format(file_path))

        line = f.readline().strip().split(' ')

        if len(line) != 2:
            f.close()
            raise Exception('The first line of {} is not information\
                    of size of row and column.'.format(file_path))

        self.row = int(line[0])
        self.column = int(line[1])

        for i, line in enumerate(f):
            row = []

            for j, kind_num in enumerate(line.strip().split()):
                num = int(kind_num)
                p = _Point(i, j, Maze.Kind(num))
                row.append(p)

                if num == Maze.Kind.STARTING.value:
                    self.start = p

                if num == Maze.Kind.EXIT.value:
                    self.exits.append(p)

            self.points.append(row)

        f.close()

    def print_maze(self):
        if not self.points:
            print('Maze is not initialized.')
            return

        print('Maze({}X{})'.format(self.row, self.column))
        for row in self.points:
            for point in row:
                print('{} '.format(point), end='')
            print('')

    def print_path(self):
        if not self.path:
            print('It is not computed yet.')
            return

        count = len(self.path) - 1
        i = 0

        while i < count:
            p = self.path[i]
            print('({}, {}) -> '.format(p.x, p.y), end='')
            i += 1
        else:
            p = self.path[i]
            print('({}, {})'.format(p.x, p.y))
            print('---')
            print('length: {}'.format(self.length))
            print('time: {}'.format(self.movement))

    def write(self):
        if not self.path:
            return
        
        try:
            output = open('output.txt', 'w')
        except IOError:
            print('Could not write file.')

        for row in self.points:
            point_iter = iter(row)
            current_point = None
            next_point = next(point_iter)

            while True:
                try:
                    current_point = next_point
                    next_point = next(point_iter)
                    output.write('{} '.format(current_point.kind.value))

                except StopIteration:
                    output.write('{}\n'.format(current_point.kind.value))
                    break
        output.write(
            '---\nlength: {}\ntime: {}'.format(self.length, self.movement)
        )

    def __clear_maze(self):
        for row in self.points:
            for p in row:
                p.eval = False

    def __look_around(self, point):
        points = []
        prev = point.prev
        x = point.x
        y = point.y

        # Left
        if y != 0 and prev != Maze.Direction.LEFT:
            p = self.points[x][y-1]

            if p.eval == False and p.kind != Maze.Kind.WALL:
                p.prev = Maze.Direction.RIGHT
                points.append(p)

        # Down
        if x != self.row and prev != Maze.Direction.DOWN:
            p = self.points[x+1][y]

            if p.eval == False and p.kind != Maze.Kind.WALL:
                p.prev = Maze.Direction.UP
                points.append(p)

        # Right
        if y != self.column and prev != Maze.Direction.RIGHT:
            p = self.points[x][y+1]

            if p.eval == False and p.kind != Maze.Kind.WALL:
                p.prev = Maze.Direction.LEFT
                points.append(p)

        # Up
        if x != 0 and prev != Maze.Direction.UP:
            p = self.points[x-1][y]

            if p.eval == False and p.kind != Maze.Kind.WALL:
                p.prev = Maze.Direction.DOWN
                points.append(p)

        return points

    def __construct_path(self, exit):
        self.path = [exit]
        p = self.__move_previous(exit)

        while p.kind != Maze.Kind.STARTING:
            p.kind = Maze.Kind.PATH
            self.path.append(p)
            p = self.__move_previous(p)
        else:
            self.path.append(p)
            self.path.reverse()
            self.length = len(self.path) - 2

    def __move_previous(self, p):
        if p.prev == Maze.Direction.UP:
            return self.points[p.x-1][p.y]

        elif p.prev == Maze.Direction.RIGHT:
            return self.points[p.x][p.y+1]

        elif p.prev == Maze.Direction.DOWN:
            return self.points[p.x+1][p.y]

        elif p.prev == Maze.Direction.LEFT:
            return self.points[p.x][p.y-1]

        else:
            return None

    def __manhattan_distance(self, point):
        distance = []

        for p in self.exits:
            x = abs(point.x - p.x)
            y = abs(point.y - p.y)
            distance.append(x + y)

        return min(distance)

class _Point():
    def __init__(self, x, y, kind):
        self.x = x
        self.y = y
        self.kind = kind
        self.eval = False
        self.distance = 0
        self.prev = Maze.Direction.NONE

    def __str__(self):
        return '{}({}, {})'.format(self.kind, self.x, self.y)

    def __repr__(self):
        return '{}({}, {})'.format(self.kind, self.x, self.y)

def main():
    if sys.version_info[0] < 3:
        raise Exception('Must be using Python 3.')

    if len(sys.argv) < 2:
        raise Exception('File path must be given.')

    file_path = sys.argv[1]
    print('Command line argument: {}'.format(file_path))

    foo = Maze(file_path)
    foo.print()

if __name__ == '__main__':
    main()

