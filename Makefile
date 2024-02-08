CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -g
EXEC = test
OBJECTS = main.o sphere.o plane.o cylinder.o camera.o hittableList.o material.o hittable.o interval.o ray.o vec3.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
