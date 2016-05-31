#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void logErro(int cod, const char * description) {
    // imprime no console ou grava em arquivo.
    // se for gravar em arquivo, deve-se ter atenção de abrir e fechar arquivo a cada gravação
}

void resize(GLFWwindow* window, int width, int height) {
    // redefine propriedades do volume de visualização e tamanho da viewport
    // glViewport...
    std::cout << "resize\n";
}

void init() {
    float points[] = {0.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f};
    GLuint pointsVBO = 0;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    float colors[] = {0.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f};
    GLuint colorsVBO = 0;
    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // habilitado primeiro atributo do vbo bound atual
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO); // identifica vbo atual
    // associação do vbo atual com primeiro atributo
    // 0 identifica que o primeiro atributo está sendo definido
    // 3, GL_FLOAT identifica que dados são vec3 e estão a cada 3 float.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // é possível associar outros atributos, como normais, mapeamento e cores
    // lembre-se: um por vértice!
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    // note que agora o atributo 1 está definido
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // habilitado segundo atributo do vbo bound atual
    glEnableVertexAttribArray(1);
    
//    std::string v_shader = "#version 410\n\
//    layout(location=0) in vec3 vp;\
//    layout(location=1) in vec3 vc;\
//    out vec3 color;\
//    void main () {\
//       color = vc;\
//       gl_Position = vec4 (vp, 1.0);\
//    }";
//    
////    auto teste = s.c_str();
//    
//    
//    glCompileShader(v_shader);
//    glCompileShader(f_shader);
//    glAttachShader(s_program, v_shader);
//    glAttachShader(s_program, f_shader);
//    glBindAttribLocation(s_program, 0, “vp”);
//    glBindAttribLocation(s_program, 0, “vc”);
//    glLinkProgram(s_program);
}

int main(void) {
    if (!glfwInit ()) {
        std::cout << "ERROR: could not start GLFW3\n";
        return 1;
    }
    
    // Caso necessário, definições específicas para SOs, p. e. Apple OSX
    // Definir como 3.2 para Apple OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow (640, 480, "Teste de versão OpenGL", NULL, NULL);
    if (!window) {
        std::cout  << "ERROR: could not open window with GLFW3\n";
        glfwTerminate();
        return 1;
    }
    
    // callbacks
    glfwSetWindowSizeCallback(window, resize);
    glfwSetErrorCallback(logErro);
    
    glfwMakeContextCurrent(window);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // inicia manipulador da extensão GLEW
    glewExperimental = GL_TRUE;
    glewInit ();

    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL (versão suportada) %s\n", glGetString(GL_VERSION));

    init();
    
    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();
    
    std::cout << "SUCCESS\n";
    return 0;
}