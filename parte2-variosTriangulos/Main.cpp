#include<iostream>      //Librería para mostrar mensajes en la consola
#include<glad/glad.h>   //Librería para manejar funciones modernas de OpenGL
#include<GLFW/glfw3.h>  //Librería para crear ventanas y manejar teclado/ratón

//Para hacer que la gráfica ponga los puntos (vértices)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"   //Recibe una posición en 3D
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //Para colocar el punto en la pantalla
"}\0";

//Para darle el color naranja
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n" //Acá se cambia el color
"}\n\0";

//Coordenadas del triángulo
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //Inner down
};


GLuint indices[] =
{
	0, 3, 5, //Lower left triangle
	3, 2, 4, //Upper triangle
	5, 4, 1 //Lower right triangle
};


int main()
{
	//Para usar ventanas y gráficos
	glfwInit();

	//Versión de OPEN GL y en modo moderno
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Crear la ventana para mostrar el contenido de 800x800 píxeles 
	GLFWwindow* window = glfwCreateWindow(800, 800, "Programa", NULL, NULL);
	if (window == NULL) // Si falla la creación, mostramos un error y cerramos
	{
		std::cout << "No se pudo crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Activar la ventana que antes creamos
	glfwMakeContextCurrent(window);

	//Cargar las funciones de OpenGL
	gladLoadGL();

	//Para que se dibuje de extremo a extremo
	glViewport(0, 0, 800, 800);


	//Para manejar la posición de los vértices
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Para los colores
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Se empaqueta el de los vértices con los colores
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Y para borrar los archivos separados que ahora están unificados
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VAO y VBO son como "cajas" para guardar la información del triángulo
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//EBO para triángulo relleno
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Configuración de atributos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//BUCLE PARA MANTENER EL DIBUJO
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Limpieza de buenas prácticas :D
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
