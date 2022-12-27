#version 460 core

out vec4 out_Color;

in vec4 color;
in float distance;
in float angle;

layout(binding = 0) uniform sampler2D coverage;
const float remap = 1.41421356237;

float covarage(){
	if(distance >= 0){
		return clamp(texture(coverage, vec2(distance * remap, angle)).x / 2, 0, 1);
	}

	return clamp(1 - texture(coverage, vec2(-distance* remap, angle)).x / 2, 0, 1);
	
}

void main(void){
	out_Color = vec4(color.rgb, color.a * covarage());
}