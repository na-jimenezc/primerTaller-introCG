#version 330 core // Versión del shader

out vec4 FragColor; // Salida del color en formato RGBA

in vec3 color; // Entrada del color desde el Vertex Shader
in vec2 texCoord; // Entrada de coordenadas de textura desde el Vertex Shader

uniform sampler2D tex0; // Uniforme que representa la unidad de textura

void main()
{
	FragColor = texture(tex0, texCoord); // Toma el color de la textura en las coordenadas dadas
}
