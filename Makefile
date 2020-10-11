IDIR=./include
IOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include
LOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/x64/mingw/bin
# IEXIV2=C:/dev/exiv2-0.27.3-MinGW64/include
# LEXIV2=C:/dev/exiv2-0.27.3-MinGW64/bin
LDLIBS= -llibopencv_core411 -llibopencv_highgui411 -llibopencv_imgcodecs411 -llibopencv_imgproc411 #-lexiv2

CC=g++
CFLAGS=-Wall -g -I ${IDIR} -I ${IOPENCV} -L ${LOPENCV} ${LDLIBS}
DEPS = $(wildcard ${IDIR}/*.hpp)
SOURCES= $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, ${SOURCES})

.PHONY: all clean

default: all

all: sample

%.o: %.cpp $(DEPS)
	${CC} -c $^ -I ${IDIR} -I ${IOPENCV}

sample: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJECTS) ${wildcard ${IDIR}/*.gch}

destroy:
	$(RM) $(OBJECTS) sample ${wildcard ${IDIR}/*.gch}

# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
