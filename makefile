OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	g++ -c $< -o $@

a.out: $(OBJECTS)
	g++ $(OBJECTS) -o $@