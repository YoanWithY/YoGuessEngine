CC=gcc

GAME_SRC=main.c aGLFWWindow.c aVAO.c aShader.c aFramebuffer.c aScene.c aList.c aArrayList.c svg.c vec2.c vec3.c vec4.c
LIB_PATH=C:/Users/yoatc/Documents/clibs
LIBS=glfw-3.3.8.bin.WIN64/lib-mingw-w64
GLFW=glfw-3.3.8.bin.WIN64/include
GLEW=glew-2.1.0/include/GL

YoGuessEngine: $(GAME_SRC)
	$(CC) -o YoGuessEngine.exe $(GAME_SRC) -Wall -Wformat=0 -g -L $(LIBS) -l glfw3 -l gdi32 -l opengl32 -l glew32 -l glu32 -I $(GLEW) -I $(GLFW)