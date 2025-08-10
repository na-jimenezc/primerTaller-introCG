#include"shaderClass.h" 


//Funci�n que lee un archivo de texto y devuelve todo su contenido como un string
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary); //Abrimos el archivo en modo binario
	if (in) //Si el archivo se abri� correctamente
	{
		std::string contents;          //Aqu� guardaremos el contenido
		in.seekg(0, std::ios::end);    //Nos movemos al final del archivo
		contents.resize(in.tellg());   //Reservamos espacio seg�n el tama�o del archivo
		in.seekg(0, std::ios::beg);    //Volvemos al inicio del archivo
		in.read(&contents[0], contents.size()); //Leemos todo el archivo en "contents"
		in.close();                    //Cerramos el archivo
		return(contents);              //Devolvemos el contenido
	}
	throw(errno);
}


//Crea un "programa de shader" usando un archivo de v�rtices y uno de fragmentos
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Leemos el c�digo del archivo de v�rtices y del archivo de fragmentos
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Convertimos el texto le�do en un formato que OpenGL entiende (char*)
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Se crea y compila el Shader de v�rtices
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Se crea el objeto
	glShaderSource(vertexShader, 1, &vertexSource, NULL);    //Se le pasa el c�digo
	glCompileShader(vertexShader);                           //Se compila

	//Se crea y compila el Shader de fragmentos
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//Se crea el programa completo
	ID = glCreateProgram();                     //Creamos el programa donde unir los shaders
	glAttachShader(ID, vertexShader);           //Pegamos el shader de v�rtices
	glAttachShader(ID, fragmentShader);         //Pegamos el shader de fragmentos
	glLinkProgram(ID);                          //Los enlazamos para formar un solo programa

	//Limpiar shaders sueltos
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Shader::Activate()
{
	glUseProgram(ID); //Indicamos a OpenGL que queremos usar este shader
}

void Shader::Delete()
{
	glDeleteProgram(ID); //Elimina el programa de shaders
}
