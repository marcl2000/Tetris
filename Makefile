CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
EXEC = biquadris
OBJECTS = main.o grid.o graphicsdisplay.o cell.o levelone.o leveltwo.o levelthree.o window.o textdisplay.o line.o shape.o levelzero.o level.o IShape.o SShape.o JShape.o LShape.o OShape.o ZShape.o TShape.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} 
