#version 330 core
//Misma versión de antes

out vec4 FragColor;
//Variable de salida del fragment shader.
//Aquí escribiremos el color final que tendrá cada "fragmento" (pixel en pantalla).


//Inputs the color from the Vertex Shader
in vec3 color;

void main()
{
    //Asignamos un color al fragmento.
    //vec4(r, g, b, a) con valores entre 0.0 y 1.0
    // r = rojo, g = verde, b = azul, a = alpha (opacidad).

    FragColor = vec4(color, 1.0f);

    //En este caso: 1.0 rojo, 1.0 verde, 0.0 azul → amarillo puro.
    //a = 1.0 → completamente opaco.
}
