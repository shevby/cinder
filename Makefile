all: rebuild

.gitignore:
	printf ".gitignore\nbuild\n" > .gitignore

rebuild: clean buildall

buildall:
	cd build && cmake .. && make

clean: .gitignore
	rm -rf build
	mkdir build