grafika1:
	g++ grafika1.cpp FrameBuffer.cpp DrawMap.cpp -o grafika1 -std=c++11

grafika2:
	g++ grafika2.cpp FrameBuffer.cpp Line.cpp Drawing.cpp LetterWriter.cpp -o grafika2 -std=c++11
	
grafika3:
	g++ grafika3.cpp FrameBuffer.cpp Line.cpp Drawing.cpp FloodFillDrawing.cpp -o grafika3 -std=c++11
	
grafika4:
	g++ grafika4.cpp FrameBuffer.cpp KeyboardInputListener.cpp Point.cpp Line.cpp Drawing.cpp FloodFillDrawing.cpp -o grafika4 -std=c++11
	
grafika5:
	g++ grafika5.cpp FrameBuffer.cpp KeyboardInputListener.cpp Point.cpp Line.cpp Drawing.cpp -o grafika5 -std=c++11
	
clean:
	-rm -rf grafika1 grafika2 grafika3 grafika4
