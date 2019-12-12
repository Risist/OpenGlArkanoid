
includePaths = -IC:/Libs/SFML-2.5.1-gcc/include -IC:/Libs/glew-2.1.0/include -IC:/Libs/glm
libPaths = -LC:/Libs/SFML-2.5.1-gcc/lib -LC:/Libs/glew-2.1.0-gcc/lib 
lib = -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lglew32

Outputs = Background.o Ball.o Bricks.o Collision.o GameObject.o GameObjectTriangle.o Paddle.o Pause.o RenderObject.o Walls.o main.o WinLoose.o Border.o
cpp = Background.cpp Ball.cpp Bricks.cpp Collision.cpp GameObject.cpp GameObjectTriangle.cpp Paddle.cpp Pause.cpp RenderObject.cpp Walls.cpp main.cpp WinLoose.cpp Border.cpp

flags = -std=c++17 -w

default: compile link
clean:
	rm *.o *.out *~

compile: 
	g++ -c $(cpp) $(includePaths) $(flags)
link:
	g++ $(Outputs)  -o output $(libPaths) $(lib) $(flags)