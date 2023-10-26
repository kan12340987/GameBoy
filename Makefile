all:
	g++ -std=c++17 src/emu_core.cpp -o emu_core

clean:
	$(RM) hello