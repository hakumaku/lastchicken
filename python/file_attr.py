text = open('./sample.txt', 'w')
text.write('Hello World!!\n')
list_temp = ['Hello World!!\n', 'Bye World!!\n', 'I\n', 'love\n', 'HOTS\n']
text.writelines(list_temp)
text.close()

#
# file.read(): reads at most size
# file.readline(): reads one entire line
# file.readlines(): reads until EOF using readline()
#
# It is a bad idea to read the whole of a file at once.
# Since it is iterable, you better read line by line.
#

text = open('./sample.txt', 'r')
line = text.readline()
print('{}({})'.format(line, text.tell()))
line = text.readline()
print('{}({})'.format(line, text.tell()))

text.close()