#version 330 core
//OpenGL Shading Language - versi�n "330 core" corresponde a OpenGL 3.3 con el perfil "core".

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//'layout (location = 0)' indica que este atributo de entrada
//vendr� desde el VAO/VBO en la posici�n 0 (cuando lo configuramos en el programa principal).
//'vec3' significa que recibimos 3 valores (x, y, z) para cada v�rtice.

out vec3 color;
uniform float scale;

void main()
{
    //gl_Position es una variable especial de OpenGL que representa
    //la posici�n final del v�rtice en coordenadas de "clip space"
    //(el espacio que usa la GPU antes de hacer la proyecci�n a la pantalla).

    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    color = aColor;

    //vec4(aPos, 1.0) convierte nuestro vec3 (x, y, z) en un vec4 (x, y, z, w)
    //donde w=1.0 es necesario para las operaciones de proyecci�n.
}
