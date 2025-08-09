#include "VAO.h" 

//Constructor que crea un VAO (Vertex Array Object)
VAO::VAO()
{
    //Crea un nuevo VAO y guarda su identificador único en la variable ID
    //son las instrucciones para dibujar el triángulo
    glGenVertexArrays(1, &ID);
}


/*Se linkea el VBO(Vertex Buffer Object) al VAO*/
//"En esta caja (VAO), guárdame las instrucciones de cómo leer los datos del VBO"

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    //Se activa el VBO que tiene la info de los vértices
    VBO.Bind();

    //Definimos cómo se interpretan esos datos
    //layout → número de ranura/canal donde irá este atributo (ej: 0 = posición, 1 = color)
    //numComponents → cuántos valores forman este atributo (ej: 3 = X, Y, Z)
    //type → tipo de datos (GL_FLOAT = número decimal)
    //stride → distancia en bytes entre un vértice y el siguiente dentro del VBO
    //offset → desde qué posición dentro del vértice empieza este atributo
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

    //Activación del layout
    glEnableVertexAttribArray(layout);

    //Cerrar el VBO para no cambiarlo
    VBO.Unbind();
}

//Para usar el VAO
void VAO::Bind()
{
    glBindVertexArray(ID);
}

//Para desactivar el VAO
void VAO::Unbind()
{
    glBindVertexArray(0);
}

//Liberar espacio
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
