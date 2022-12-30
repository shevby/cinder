SOURCES = LocationMapStateCache.cpp LocationMapStateShort.cpp Gzip.cpp webserver.cpp HttpRequest.cpp location_map_poc.cpp utils.cpp
CXX_FLAGS = -pthread -std=c++20

run: all
	./a.out

all: build_app build_test

build_app:
	g++ $(CXX_FLAGS) $(SOURCES) LocationMapMain.cpp

build_test:
	g++ -E test_location_map.cpp | grep catch2_test_function_imitation_ | sed -e 's/{/;/' > /tmp/test_location_map.inc
	g++ $(CXX_FLAGS) $(SOURCES) test_location_map.cpp -o test_location_map

clean:
	rm a.out
