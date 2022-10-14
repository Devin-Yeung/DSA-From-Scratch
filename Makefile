init:
	@mkdir build 2> /dev/null || true
	@cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DUSE_SAN=ON
	@ln -s ./build/compile_commands.json ./compile_commands.json

.PHONY: build
build:
	cmake --build build

test:
	cd ./build && ctest
