LIB = -lglut -lGLU

RUN = run.cpp src/*.cpp

TEST3D = test3d.cpp src/*.cpp

TESTCAM = testCam.cpp src/*.cpp

TESTMIN = testMin.cpp src/*.cpp

TESTMINX = testMinX.cpp src/*.cpp headers/*.h

TESTCAMCEU = testCamCEU.cpp src/*.cpp headers/*.h

TESTGLBASICMAIN = testGlBasicMain.cpp src/*.cpp headers/*.h

TESTTEXTURE = testTexture.cpp src/*.cpp headers/*.h

TESTOBJECTS = testObjects.cpp src/*.cpp headers/*.h

run: $(RUN)
	g++ $(RUN) $(LIB) -o $@

test3d: $(TEST3D)
	g++ $(TEST3D) $(LIB) -o $@

testCam: $(TESTCAM)
	g++ $(TESTCAM) $(LIB) -o $@
	
testMin: $(TESTMIN)
	g++ $(TESTMIN) $(LIB) -o $@

testMinX: $(TESTMINX)
	g++ $(TESTMINX) $(LIB) -o $@

testCamCEU: $(TESTCAMCEU)
	g++ $(TESTCAMCEU) $(LIB) -o $@
	
testGlBasicMain: $(TESTGLBASICMAIN)
	g++ $(TESTGLBASICMAIN) $(LIB) -o $@
	
testTexture: $(TESTTEXTURE)
	g++ $(TESTTEXTURE) $(LIB) -o $@
	
testObjects: $(TESTOBJECTS)
	g++ $(TESTOBJECTS) $(LIB) -o $@

clean:
	rm ./run
	rm ./test3d
