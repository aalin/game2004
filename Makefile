default: game

game: src
	$(MAKE) -j -C src/

clean:
	$(MAKE) -C src/ clean
