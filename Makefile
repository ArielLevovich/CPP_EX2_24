CXX=g++
CXXFLAGS=-std=c++11 -g -Werror -Wall -Wextra
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp Demo.cpp
#SOURCES=Graph.cpp Algorithms.cpp Demo.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: test 
#run: demo
	./$^

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo
	rm -f *.o demo test
