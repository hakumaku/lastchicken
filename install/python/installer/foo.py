import tarfile
import pathlib

with tarfile.open('./st-0.8.2.tar.gz') as tf:
    foo = tf.getnames()
    bar = tf.getmembers()

print(foo)
print(bar)

