
proj3.x: test.o
        g++47 -std=c++11 -o proj3.x test.o
test.o: test.cpp
        g++47 -std=c++11 -c test.cpp
clean:
        rm *.o proj3.x

