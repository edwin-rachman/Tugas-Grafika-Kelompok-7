grafika_UTS:
	g++ grafika_UTS.cpp FrameBuffer.cpp KeyboardInputListener.cpp MouseInputListener.cpp Point.cpp Line.cpp Drawing.cpp CharBuilder.cpp FilledDrawing.cpp IntersectionMap.cpp ShapeBuilder.cpp TextObject.cpp -o grafika_UTS -std=c++11

clean:
	-rm -rf grafika_UTS
