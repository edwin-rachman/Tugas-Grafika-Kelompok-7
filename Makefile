grafika1:
	g++ grafika1.cpp FrameBuffer.cpp DrawMap.cpp -o grafika1 -std=c++11

grafika2:
	g++ grafika2.cpp CharBuilder.cpp FrameBuffer.cpp Line.cpp Drawing.cpp -o grafika2 -std=c++11
	
clean:
	-rm -rf grafika1 grafika2
