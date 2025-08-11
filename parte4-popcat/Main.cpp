#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Coordenadas de los vértices //     COORDENADAS     /     COLORES     /   TexCoord  //
GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Esquina inferior izquierda
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Esquina superior izquierda
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Esquina superior derecha
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Esquina inferior derecha
};

// Índices para el orden de los vértices
GLuint indices[] =
{
	0, 2, 1, // Triángulo superior
	0, 3, 2  // Triángulo inferior
};

int main()
{
	// Inicializa GLFW
	glfwInit();

	// Especifica la versión de OpenGL (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Versión mayor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Versión menor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil Core

	// Crea una ventana de 800x800 píxeles
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL) // Verifica si la ventana se creó correctamente
	{
		std::cout << "Failed to create GLFW window" << std::endl; // Mensaje de error
		glfwTerminate(); // Finaliza GLFW
		return -1; // Sale del programa
	}
	glfwMakeContextCurrent(window); // Hace que la ventana sea el contexto actual

	// Carga GLAD para configurar OpenGL
	gladLoadGL();

	// Define el viewport (área de renderizado) de OpenGL
	glViewport(0, 0, 800, 800); // Desde (0,0) hasta (800,800)

	// Crea el objeto Shader con los archivos de vértices y fragmento
	Shader shaderProgram("default.vert", "default.frag");

	// Crea y enlaza el VAO (Vertex Array Object)
	VAO VAO1;
	VAO1.Bind(); // Enlaza el VAO

	// Crea y enlaza el VBO (Vertex Buffer Object)
	VBO VBO1(vertices, sizeof(vertices)); // Enlaza los vértices

	// Crea y enlaza el EBO (Element Buffer Object)
	EBO EBO1(indices, sizeof(indices)); // Enlaza los índices

	// Define los atributos del VBO (posición, color, coordenadas de textura)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // Posición
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Textura

	// Desenlaza VAO, VBO y EBO para evitar modificaciones accidentales
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Obtiene el ID del uniform llamado "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Crea la textura usando la clase Texture
	Texture popCat("popcat.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); // Carga la imagen
	popCat.texUnit(shaderProgram, "tex0", 0); // Asigna la unidad de textura al shader

	// Bucle principal
	while (!glfwWindowShouldClose(window)) // Mientras la ventana no deba cerrarse
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Color de fondo
		glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

		shaderProgram.Activate(); // Activa el shader
		glUniform1f(uniID, 0.5f); // Asigna valor a la variable uniforme "scale"

		popCat.Bind(); // Enlaza la textura para renderizar

		VAO1.Bind(); // Enlaza el VAO

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Dibuja los triángulos

		glfwSwapBuffers(window); // Intercambia los buffers
		glfwPollEvents(); // Procesa los eventos de ventana
	}

	// Elimina todos los objetos creados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window); // Destruye la ventana
	glfwTerminate(); // Termina GLFW
	return 0; // Fin del programa
}
