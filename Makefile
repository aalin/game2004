default: game

game: src
	make -j 4 -C src/

clean:
	make -C src/ clean
