NUM_CORES=$(grep -c ^processor /proc/cpuinfo)

default: game

game: src
	make -j ${NUM_CORES} -C src/

clean:
	make -C src/ clean
