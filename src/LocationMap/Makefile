run: all
	./a.out

all: build_app build_test

build_app:
	g++ location_map_poc.cpp Gzip.cpp webserver.cpp -pthread

build_test:
	g++ test_location_map.cpp Gzip.cpp webserver.cpp -pthread -o test_location_map

clean:
	rm a.out
