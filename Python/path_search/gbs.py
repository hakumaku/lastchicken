#!/usr/bin/python3
from maze import Maze
import sys

class GreeBestFirst(Maze):
    def __init__(self, file_path, *args, **kwargs):
        super().__init__(file_path, args, kwargs)

    def search(self):
        count = self.row * self.column

        print('Finding a nearest exit...')
        p = self.__nearest_search()
        if p:
            print('Constructing path...')
            self._Maze__construct_path(p)
            print('Done')

    def __nearest_search(self):
        branching = []
        p = self.start
        movement = 0

        while True:
            if p.kind == Maze.Kind.EXIT:
                self.movement = movement
                return p

            points = self._Maze__look_around(p)
            for next_point in points:
                prior = self._Maze__manhattan_distance(next_point)

                if branching:
                    for idx, item in enumerate(branching):
                        if prior < item[0]:
                            branching.insert(idx, [prior, next_point])
                            break
                else:
                    branching.append([prior, next_point])

            # At least one path exists.
            if branching:
                movement += 1
                p = branching.pop()[1]
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

    foo = GreeBestFirst(file_path)
    foo.search()
    foo.write()

if __name__ == '__main__':
    main()

