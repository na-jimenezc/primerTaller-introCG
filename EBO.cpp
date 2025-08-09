#include "EBO.h"  


//Constructor que crea un EBO (Element Buffer Object)
//y carga en él los índices que indican el orden de los vértices

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    //Creamos un nuevo EBO y guardamos su identificador único en ID
    //Como una "lista numerada" para deciren qué orden usar los puntos guardados en el VBO
    glGenBuffers(1, &ID);

    //Se activa la lista para usarla
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    /*Copiamos los índices dentro de la lista
    //GL_ELEMENT_ARRAY_BUFFER → tipo de bolsa (para índices)
    //size → tamaño total en bytes de los índices
    //indices → puntero al arreglo con los números
    / GL_STATIC_DRAW → indica que no vamos a cambiar mucho esta lista*/
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}



void EBO::Bind()
{
    //Bind = "Abrir la lista de índices"
    //Le dice a OpenGL que este EBO es el que vamos a usar
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}


void EBO::Unbind()
{
    //Unbind = "Cerrar la lista"
    //Desactivar el EBO actual
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void EBO::Delete()
{
    //Delete = Borrar
    //Liberar la memoria
    glDeleteBuffers(1, &ID);
}
