#version 330 core // Versión del shader

layout (location = 0) in vec3 aPos; // Atributo de entrada: posición del vértice
layout (location = 1) in vec3 aColor; // Atributo de entrada: color del vértice
layout (location = 2) in vec2 aTex; // Atributo de entrada: coordenadas de textura

out vec3 color; // Salida: color hacia el fragment shader
out vec2 texCoord; // Salida: coordenadas de textura hacia el fragment shader

uniform float scale; // Uniforme que escala la posición del vértice

void main()
{
	gl_Position = vec4(scale * aPos, 1.0); // Calcula la posición final del vértice con escala
	color = aColor; // Pasa el color al fragment shader
	texCoord = aTex; // Pasa las coordenadas de textura al fragment shader
}