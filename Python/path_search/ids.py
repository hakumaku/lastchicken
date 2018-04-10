#!/usr/bin/python3
from maze import Maze
import sys

class IterativeDeepening(Maze):
    def __init__(self, file_path, *args, **kwargs):
        super().__init__(file_path, args, kwargs)

    def search(self):
        count = self.row * self.column

        print('Finding a nearest exit...')
        for i in range(count):
            p = self.__nearest_search(i)
            if p:
                print('Constructing path...')
                self._Maze__construct_path(p)
                print('Done')
                break
            else:
                self._Maze__clear_maze()

    def __nearest_search(self, depth):
        branching = []
        p = self.start
        movement = 0

        while True:
            if p.kind == Maze.Kind.EXIT:
                self.movement = movement
                return p

            if p.distance < depth:
                points = self._Maze__look_around(p)
                for i in points:
                    # distance is used as depth
                    i.distance = p.distance + 1
                    branching.append(i)

            # At least one path exists.
            if branching:
                movement += 1
                p = branching.pop()
                p.eval = True

            # Dead end
            else:
                return None

def main():
    if sys.version_info[0] < 3:
        raise Exception('Must be using Python 3.')

    if len(sys.argv) < 2:
        raise Exception('File path must be given.')
    
    file_path = sys.argv[1]
    print('Command line argument: {}'.format(file_path))

    foo = IterativeDeepening(file_path)
    foo.search()
    foo.write()

if __name__ == '__main__':
    main()

