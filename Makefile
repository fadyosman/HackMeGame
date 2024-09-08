all:
	$(CXX) -o hackmegame game.cpp core/node.cpp core/sprite.cpp player.cpp main.cpp bullet.cpp ufo.cpp -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11
