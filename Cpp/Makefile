CC = g++
CPPFLAGS = -O2 -std=c++14 
LDFLAGS = 
LDLIBS = 

CPPSRC = reading.cpp
OBJS = main.o

main.exe: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

main.o: $(CPPSRC)
	$(CC) $(CPPFLAGS) -o $@ -c $^

clean:
	rm *.o

