#extension GL_ARB_gpu_shader_fp64 : enable
uniform vec2 lightLocation;
uniform vec4 lightColor;
uniform vec4 globalLight;
uniform float radius;

void main() {
	float distance = length(lightLocation - gl_FragCoord.xy);
	float attenuation = 75 / distance;
	vec4 color = vec4(attenuation, attenuation, attenuation, pow(attenuation, 3)) * vec4(lightColor);

	gl_FragColor = color;

}

