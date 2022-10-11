hello-world: build-lua
	g++ hello.cpp \
		-I build/lua-`cat lua_version`/src/ \
		build/lua-`cat lua_version`/src/liblua.a \
		-ldl \
		-o build/hello

build-lua: download_lua
	make -C build/lua-`cat lua_version`

download_lua:
	mkdir -p build
	wget https://www.lua.org/ftp/lua-`cat lua_version`.tar.gz -O build/lua.tar.gz
	tar -xf build/lua.tar.gz -C build

clean:
	rm -rf build
