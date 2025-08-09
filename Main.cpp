#include<iostream>      //Librer�a para mostrar mensajes en la consola
#include<glad/glad.h>   //Librer�a para manejar funciones modernas de OpenGL
#include<GLFW/glfw3.h>  //Librer�a para crear ventanas y manejar teclado/rat�n

//Para hacer que la gr�fica ponga los puntos (v�rtices)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"   //Recibe una posici�n en 3D
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //Para colocar el punto en la pantalla
"}\0";

//Para darle el color naranja
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n" //Ac� se cambia el color
"}\n\0";

int main()
{
	//Para usar ventanas y gr�ficos
	glfwInit();

	//Versi�n de OPEN GL y en modo moderno
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Crear la ventana para mostrar el contenido de 800x800 p�xeles 
	GLFWwindow* window = glfwCreateWindow(800, 800, "Programa", NULL, NULL);
	if (window == NULL) // Si falla la creaci�n, mostramos un error y cerramos
	{
		std::cout<<"No se pudo crear la ventana"<<std::endl;
		glfwTerminate();
		return -1;
	}

	//Activar la ventana que antes creamos
	glfwMakeContextCurrent(window); 

	//Cargar las funciones de OpenGL
	gladLoadGL();

	//Para que se dibuje de extremo a extremo
	glViewport(0, 0, 800, 800);


	//Para manejar la posici�n de los v�rtices
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Para los colores
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Se empaqueta el de los v�rtices con los colores
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Y para borrar los archivos separados que ahora est�n unificados
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Coordenadas :D
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Esquina inferior izquierda
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //Esquina inferior derecha
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //Parte de arriba
	};

	//VAO y VBO son como "cajas" para guardar la informaci�n del tri�ngulo
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Activaci�n del VAO
	glBindVertexArray(VAO); 

	//El VBO guarda la informaci�n de los v�rtices
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 

	//Guardar los datos del tri�ngulo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	//Instrucciones para la lectura de datos + la activaci�n de la configuraci�n
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	//Cerrar las configuraciones para no tocarlas
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//QUIZ - SE A�ADE LA CONFIGURACI�N DE SOLAMENTE DIBUJAR LAS L�NEAS
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//BUCLE PARA MANTENER EL DIBUJO
	while (!glfwWindowShouldClose(window))
	{
		//Se pinta la ventana con un color oscuro
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //Se borra la pantalla antes de dibujar

		//Usamos nuestro programa (posici�n + color)
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); //Activar el tri�ngulo
		glDrawArrays(GL_TRIANGLES, 0, 3); //Dibujar el tri�ngulo

		glfwSwapBuffers(window); //Mostramos el dibujo en pantalla
		glfwPollEvents();        //Revisamos si el usuario hizo algo (teclado, rat�n, etc.)
	}

	//Limpieza de buenas pr�cticas :D
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}




/*int main() {
	glfwInit(); //Cada vez que se inicia una funci�n, se tiene que terminar

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Para indicar la versi�n que se est� utilizando de open gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Core: modernas, Compatibility: modernas y viejas, UN PERFIL ES UNA MANO DE LIBRERIAS

	//Triangulito :D
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // left cornet, right corner, top corner = coordenada
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  //Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //Inner left
	};

	//Se da el orden de visitas para generar el tri�ngulo interno
	GLuint indices[]{
		0,3,5,
		3,2,4,
		5,4,1
	};

	//Se usa por referencia a los objetos, como los shaders

	GLFWwindow* window = glfwCreateWindow(800, 800, "primerTaller", NULL, NULL); //Para crear ventana: ancho, largo, nombre, completa y non-important

	if (window == NULL) {
		std::cout << "Se fall� en crear la ventana GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //Cargar el contexto (objeto de OPENGL)	

	gladLoadGL(); //Descargar configuraciones de openGL


    glViewport(0, 0, 800, 800); //Bottom left corner a top left  - x=0 y=0 a x=800, y=800

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Valor de referencia, un spring, el source code
	glCompileShader(vertexShader); //Se tiene que compular

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
	glCompileShader(fragmentShader); 

	//Se tiene que empaquetar en un Shader Program para usarlos y se hace el atach con el glAttachShader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Y se matan los shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Para el buffer con la informaci�n de los v�rtices
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO); //Se crea el VAO antes del VBO
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //El static va a ser modificado un momento y usado muchas veces
																			//Din�mico que modifica y se usa mucho

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Posici�n del vertex atribute, valores por v�rtice, tipos de valores, (coordenadas como enteros), 
																	 // que tanta info hay por vertex, 
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //PARA NO CONFUNDIR VAO Y VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //CUIDADO CON EL ORDEN PORQUE PUEDES TOTEAR TODO :D




	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Red Blue Green Transparencia
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		///glDrawArrays(GL_TRIANGLES, 0, 3); //TRIANGULO ,  ,  3 VERTICES

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); //Procesar eventos pra hacer responder la ventana

	}

	//Se borra todo para mantener la memoria limpia
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window); //Siempre matar a la ventana porque puede matar al programa
	glfwTerminate();
	return 0;
    
}*/