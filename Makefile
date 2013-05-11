OBJECTS = run.cpp src/*.cpp

run: $(OBJECTS)
	g++ $(OBJECTS) -lglut -o $@
	
clean:
	rm -rf ./run
