#include"Texture.h"

// Constructor de la clase Texture
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Asigna el tipo de textura (por ejemplo, GL_TEXTURE_2D) al objeto
	type = texType;

	// Variables para almacenar ancho, alto y número de canales de color de la imagen
	int widthImg, heightImg, numColCh;

	// Indica que la imagen se voltee verticalmente al cargarla
	// (porque OpenGL considera el origen en la esquina inferior izquierda)
	stbi_set_flip_vertically_on_load(true);

	// Carga la imagen desde archivo y la almacena en un arreglo de bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Verifica si la imagen se cargó correctamente
	if (!bytes) {
		std::cerr << "Error: No se pudo cargar la imagen: " << image << std::endl;
		return; // Sale del constructor si hubo un error
	}

	// Genera un ID para un objeto de textura en OpenGL
	glGenTextures(1, &ID);
	// Activa la unidad de textura (slot) en la que se usará esta textura
	glActiveTexture(slot);
	// Enlaza el objeto de textura generado a un tipo específico (ej. GL_TEXTURE_2D)
	glBindTexture(texType, ID);

	// Configura el algoritmo de escalado de textura
	// Cuando la imagen se reduzca → usar MipMap y filtrado lineal
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	// Cuando la imagen se amplíe → usar filtrado de vecino más cercano
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configura el modo de repetición de la textura en los ejes S y T
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Ejemplo de configuración si se quisiera usar bordes fijos (comentado)
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Asigna la imagen cargada al objeto de textura en OpenGL
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Genera automáticamente los MipMaps
	glGenerateMipmap(texType);

	// Libera la memoria de la imagen cargada (ya está en la GPU)
	stbi_image_free(bytes);

	// Desenlaza la textura para evitar modificaciones accidentales
	glBindTexture(texType, 0);
}

// Asigna la unidad de textura a un uniforme del shader
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Obtiene la ubicación del uniforme en el shader
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Activa el shader antes de modificar el uniforme
	shader.Activate();
	// Asigna el número de unidad de textura al uniforme
	glUniform1i(texUni, unit);
}

// Enlaza (activa) la textura
void Texture::Bind()
{
	glBindTexture(type, ID);
}

// Desenlaza (desactiva) la textura
void Texture::Unbind()
{
	glBindTexture(type, 0);
}

// Elimina el objeto de textura de la GPU
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
