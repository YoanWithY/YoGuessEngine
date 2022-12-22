#version 460 core

in vec2 iPos;
in vec4 iColor;
in float iCoverage;

out vec4 color;
out float coverage;

uniform vec2 sceneScale;

void main(void){
	gl_Position = vec4(iPos / sceneScale + vec2(-1, 1), 0.0, 1.0);
	color = iColor;
	coverage = iCoverage;
}