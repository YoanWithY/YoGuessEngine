#version 460 core

out vec4 out_Color;

in vec4 color;
in float coverage;

void main(void){
	out_Color = vec4(color.rgb, color.a* min(coverage, 1));
}