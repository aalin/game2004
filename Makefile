default: game

game: src
	make -C src/

clean:
	make -C src/ clean
