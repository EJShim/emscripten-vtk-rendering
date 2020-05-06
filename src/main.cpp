
// #define GLFW_INCLUDE_ES3
// #include <emscripten/emscripten.h>

#include "linmath.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


GLFWwindow * window;
GLuint vertex_buffer, vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};


static const char* vertex_shader_text =
    "#version 300 es\n"
    "uniform mat4 MVP;\n"
    "in lowp vec3 vCol;\n"
    "in lowp vec2 vPos;\n"
    "out lowp vec3 i_color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
    "    i_color = vCol;\n"
    "}\n";
static const char* fragment_shader_text =
    "#version 300 es\n"
    "in lowp vec3 i_color;\n"
    "out lowp vec4 o_color;\n"
    "void main()\n"
    "{\n"
    "    o_color = vec4(i_color, 1.0);\n"
    "}\n";

void GenerateFrame() {
    float ratio;
    int width, height;
    mat4x4 m, p, mvp;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
}

int main() {



    if (!glfwInit() || !glewInit()) {
        std::cout << "Failed to Initialized" << std::endl;
    }




    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        std::cout << "fialed' <<" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "succ" << std::endl;

    glfwMakeContextCurrent(window);
    

    std::cout << "context current" << std::endl;


    glGenBuffers(1, &vertex_buffer);


    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glUseProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    std::cout << "Start Rendering" << std::endl;


    //main loop func??
    GenerateFrame();



    // emscripten_request_animation_frame_loop();
    // emscripten_set_main_loop(GenerateFrame, 0, 0);
}
