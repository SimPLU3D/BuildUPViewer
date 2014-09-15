CC=g++
CFLAGS=-Wall -std=c++11
LIBS=-lboost_system -lboost_filesystem -lgdal -losg -losgGA -losgViewer -losgUtil -lOpenThreads
EXECUTABLE=pluViewer

$(EXECUTABLE):main.cpp fileio.cpp osg.cpp
	$(CC) $(CFLAGS) main.cpp fileio.cpp osg.cpp -o $@ $(LIBS)

clean:
	rm -rf *o $(EXECUTABLE)