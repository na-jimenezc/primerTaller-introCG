#include "VBO.h"  


//VBO (Vertex Buffer Object) que tiene las coordenadas de los vértices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    //Se crea el VBO con su ID
    glGenBuffers(1, &ID);

    //Se activa
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    //Se copian los datos de los vértices al VBO
    //GL_ARRAY_BUFFER → tipo de bolsa (para datos de vértices)
    //size → tamaño total en bytes de los datos
    //vertices → puntero al arreglo con los valores (X, Y, Z, etc.)
    //GL_STATIC_DRAW → indica que los datos no van a cambiar mucho
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

//Bindear el VBO
void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//Cerrar el VBO
void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Liberar memoria
void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
