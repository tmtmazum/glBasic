LIB = -lglut -lGLU

RUN = run.cpp src/*.cpp

TEST3D = test3d.cpp src/*.cpp

TESTCAM = testCam.cpp src/*.cpp

run: $(RUN)
	g++ $(RUN) $(LIB) -o $@

test3d: $(TEST3D)
	g++ $(TEST3D) $(LIB) -o $@

testCam: $(TESTCAM)
	g++ $(TESTCAM) $(LIB) -o $@
	
clean:
	rm ./run
	rm ./test3d
