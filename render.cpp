#include "render.h"


unsigned int initShader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
	unsigned int 
		shaderProgram{ glCreateProgram() },
		vertexShader{ glCreateShader(GL_VERTEX_SHADER) },
		fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	checkShaderCompile(vertexShader);
	checkShaderCompile(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkShaderProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void checkShaderCompile(const unsigned int vertexShader) {
	int success{};
	char infoLog[512]{};

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "LOG::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	} else {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "LOG::SHADER::VERTEX::COMPILATION_SUCCESSED\n" << infoLog << std::endl;		
	}
}

void checkShaderProgram(const unsigned int shaderProgram) {
	int success {};
	char infoLog[512] {};

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "LOG::SHADER::PROGRAM:COMPILATIONFAILED\n" << infoLog << std::endl;
	} else {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "LOG::SHADER::PROGRAM::COMPILATION_SUCCESSED\n" << infoLog << std::endl;		
	}
}

unsigned int renderWithVAO(const float* vertices, const unsigned int* indices, const int verticeSize, const int indiceSize) {
	unsigned int 
		VBO,
		VAO,
		EBO;

	// Generate VBO Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// glVertexAttribPointer함수에서 사용될 정점 Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// data(vertices)를 생성한 Buffer에 복사
	glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indices, GL_STATIC_DRAW);

	// data(vertices)에 대한 정보를 전달
	// vertex 위치속성 포인터 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 0번 vertex속성을 사용가능하게 설정
	glEnableVertexAttribArray(0);

	//  vertex 색상속성 포인터 설정
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// 1번 vertex속성을 사용가능하게 설정
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

unsigned int renderWithVBO(const float* vertices) {
	unsigned int VBO;

	// Generate VBO Buffer
	glGenBuffers(1, &VBO);

	// glVertexAttribPointer함수에서 사용될 정점 Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// data(vertices)를 생성한 Buffer에 복사
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// vertex속성 포인터 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 0번 vertex속성을 사용가능하게 설정
	glEnableVertexAttribArray(0);

	// someOpenGLFunctionThatDrawsOurTriangle();

	// glDisableVertexAttribArray(0);

	return VBO;
}