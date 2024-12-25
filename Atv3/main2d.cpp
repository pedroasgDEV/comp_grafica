#include <GLFW/glfw3.h>
#include <vector>

typedef std::vector<float> point;

struct Triangle {
    point a, b, c;
};

point multiplyMatrixVector(const std::vector<std::vector<float>>& matrix, const point& vec) {
    point result(matrix.size(), 0.0f);

    for (size_t i = 0; i < matrix.size(); i++)
        for (size_t j = 0; j < vec.size(); j++)
            result[i] += matrix[i][j] * vec[j];

    return result;
}

point translation2D(float dx, float dy, const point& a) {
    std::vector<std::vector<float>> translationMatrix = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };

    return multiplyMatrixVector(translationMatrix, a);
}

point scale2D(float sx, float sy, const point& a) {
    std::vector<std::vector<float>> scaleMatrix = {
        {sx, 0,  0},
        {0,  sy, 0},
        {0,  0,  1}
    };

    return multiplyMatrixVector(scaleMatrix, a);
}

// Triângulo inicial
Triangle triangleInit = {
    {0.0f, 0.5f, 1.0f},
    {-0.5f, -0.5f, 1.0f},
    {0.5f, -0.5f, 1.0f}
};

// Triângulo escalado
Triangle scaledTriangle = {
    scale2D(1.25f, 1.25f, triangleInit.a),
    scale2D(1.25f, 1.25f, triangleInit.b),
    scale2D(1.25f, 1.25f, triangleInit.c)
};

// Triângulo com composição
Triangle compositionTriangle = {
    translation2D(0.5f, -0.2f, scaledTriangle.a),
    translation2D(0.5f, -0.2f, scaledTriangle.b),
    translation2D(0.5f, -0.2f, scaledTriangle.c)
};

// Triângulo atual
Triangle triangle = triangleInit;

// Renderiza um triângulo
void renderTriangle(const Triangle& triangle) {
    glBegin(GL_TRIANGLES);
    glVertex2f(triangle.a[0], triangle.a[1]);
    glVertex2f(triangle.b[0], triangle.b[1]);
    glVertex2f(triangle.c[0], triangle.c[1]);
    glEnd();
}

// Callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key){
            case GLFW_KEY_A:
                triangle = scaledTriangle; // Troca para o triângulo escalado
                break;
            case GLFW_KEY_C: 
                triangle = compositionTriangle; // Troca para o triângulo com composição
                break;
            case GLFW_KEY_ESCAPE: /// Se a tecla for ESC chama a função que fecha a janela
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) {
        triangle = triangleInit; // Volta ao triângulo inicial
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1024, 576, "Triangle Transformation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.55, 0, 0.90, 1);

    // Configura o callback de teclado
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderiza o triângulo atual
        glColor3f(1.0f, 0.0f, 0.0f);
        renderTriangle(triangle);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
