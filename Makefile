all: rebuild

rebuild: clean buildall

buildall:
	cd build && cmake .. && make

clean:
	rm -rf build
	mkdir build