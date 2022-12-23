CC=gcc

SRC=main.c aGLFWWindow.c aVAO.c aShader.c aFramebuffer.c aScene.c aList.c aArrayList.c svg.c basicShape.c mat2.c mat3.c vec2.c vec3.c vec4.c
LIBS=glfw-3.3.8.bin.WIN64/lib-mingw-w64
GLFW=glfw-3.3.8.bin.WIN64/include
GLEW=glew-2.1.0/include/GL

YoGuessEngine: $(GAME_SRC)
	$(CC) -o YoGuessEngine.exe $(SRC) -Wall -Wformat=0 -g -L $(LIBS) -lm -l glfw3 -l gdi32 -l opengl32 -l glew32 -l glu32 -I $(GLEW) -I $(GLFW)