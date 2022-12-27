#version 460 core

in vec2 iPos;
in vec4 iColor;
in float iDistance;
in float iAngle;

out vec4 color;
out float distance;
out float angle;

uniform vec2 sceneScale;
uniform mat3 tMat;
uniform float rotAdd;

void main(void){
	gl_Position = vec4( (tMat * vec3(iPos, 1)).xy * sceneScale + vec2(-1, 1), 0.0, 1.0);
	color = iColor;
	distance = iDistance;
	angle = mod(iAngle, 1);
}