#include <GLFW/glfw3.h>
#include <vector>

typedef std::vector<float> point;

struct Triangle {
    point a, b, c;
};

// Triângulo inicial
Triangle triangle = {
    {0.0f, 0.5f, 1.0f},
    {-0.5f, -0.5f, 1.0f},
    {0.5f, -0.5f, 1.0f}
};

// Renderiza um triângulo com cada ponto em uma cor
void renderTriangle(const Triangle& triangle) {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(triangle.a[0], triangle.a[1]);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(triangle.b[0], triangle.b[1]);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(triangle.c[0], triangle.c[1]);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1; // Irá iniciaar a biblioteca e verificar se foi iniciada corretamente

    // Irá criar e definir a janela, sua resolução, titulo e etc...
    GLFWwindow* window = glfwCreateWindow(1024, 576, "Triangle Transformation", NULL, NULL);
    // Irá verificar ser a janela foi criada corretamente
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Irá apresentar a janela no contexto atual e as cores do background
    glfwMakeContextCurrent(window);
    glClearColor(0.1, 0.1, 0.1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderiza o triângulo atual
        renderTriangle(triangle);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
