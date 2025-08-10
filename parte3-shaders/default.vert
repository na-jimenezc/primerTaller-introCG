#version 330 core
//OpenGL Shading Language - versión "330 core" corresponde a OpenGL 3.3 con el perfil "core".

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//'layout (location = 0)' indica que este atributo de entrada
//vendrá desde el VAO/VBO en la posición 0 (cuando lo configuramos en el programa principal).
//'vec3' significa que recibimos 3 valores (x, y, z) para cada vértice.

out vec3 color;
uniform float scale;

void main()
{
    //gl_Position es una variable especial de OpenGL que representa
    //la posición final del vértice en coordenadas de "clip space"
    //(el espacio que usa la GPU antes de hacer la proyección a la pantalla).

    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    color = aColor;

    //vec4(aPos, 1.0) convierte nuestro vec3 (x, y, z) en un vec4 (x, y, z, w)
    //donde w=1.0 es necesario para las operaciones de proyección.
}
