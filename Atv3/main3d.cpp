#include <GLFW/glfw3.h>
#include <vector>
#include <array>

// Representação das cooredanadas e do Cubo
typedef std::array<float, 4> point;
struct Cube {
    point a, b, c, d, e, f, g, h;
};

// Faz a multiplicação de matrizes
point multiplyMatrixVector(const std::vector<std::vector<float>>& matrix, const point& vec) {
    point result = {0.0f, 0.0f, 0.0f, 0.0f};
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < vec.size(); j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

//  Calcula a Traslação 3D
point translation3D(float dx, float dy, float dz, const point& a) {
    std::vector<std::vector<float>> translationMatrix = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    return multiplyMatrixVector(translationMatrix, a);
}

//  Calcula a escala 3D
point scale3D(float sx, float sy, float sz, const point& a) {
    std::vector<std::vector<float>> scaleMatrix = {
        {sx, 0,  0,  0},
        {0,  sy, 0,  0},
        {0,  0,  sz, 0},
        {0,  0,  0,  1}
    };
    return multiplyMatrixVector(scaleMatrix, a);
}

// Cubo inicial
Cube cubeInit = {
    {-0.3f, -0.3f, -0.3f, 1.0f}, 
    {0.3f, -0.3f, -0.3f, 1.0f},
    {0.3f, 0.3f, -0.3f, 1.0f},
    {-0.3f, 0.3f, -0.3f, 1.0f}, 
    {-0.3f, -0.3f, 0.3f, 1.0f},
    {0.3f, -0.3f, 0.3f, 1.0f},
    {0.3f, 0.3f, 0.3f, 1.0f},
    {-0.3f, 0.3f, 0.3f, 1.0f}
};

// Cubo escalado
Cube scaledCube = {
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.a),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.b),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.c),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.d),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.e),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.f),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.g),
    scale3D(1.25f, 1.25f, 1.25f, cubeInit.h)
};

// Cubo cpm composição de traslação e escala
Cube compositionCube = {
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.a),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.b),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.c),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.d),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.e),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.f),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.g),
    translation3D(0.5f, -0.2f, 0.3f, scaledCube.h)
};

// Atual atual
Cube cube = cubeInit;

// Faz a projeção das coordenadas 3D para 2D
point project3DTo2D(const point& a, float focalLength = 1) {
    float factor = focalLength / (a[2] + 1.0f);
    return {a[0] * factor, a[1] * factor, 0.0f, 1.0f};
}

// Renderiza o Cubo
void renderCube(const Cube& in) {
    // Faz a progeção das coordenas
    Cube cube = {
        project3DTo2D(in.a),
        project3DTo2D(in.b),
        project3DTo2D(in.c),
        project3DTo2D(in.d),
        project3DTo2D(in.e),
        project3DTo2D(in.f),
        project3DTo2D(in.g),
        project3DTo2D(in.h)
    };

    // Renderiza
    glBegin(GL_LINES);
        glVertex2f(cube.a[0], cube.a[1]); glVertex2f(cube.b[0], cube.b[1]);
        glVertex2f(cube.b[0], cube.b[1]); glVertex2f(cube.c[0], cube.c[1]);
        glVertex2f(cube.c[0], cube.c[1]); glVertex2f(cube.d[0], cube.d[1]);
        glVertex2f(cube.d[0], cube.d[1]); glVertex2f(cube.a[0], cube.a[1]);

        glVertex2f(cube.e[0], cube.e[1]); glVertex2f(cube.f[0], cube.f[1]);
        glVertex2f(cube.f[0], cube.f[1]); glVertex2f(cube.g[0], cube.g[1]);
        glVertex2f(cube.g[0], cube.g[1]); glVertex2f(cube.h[0], cube.h[1]);
        glVertex2f(cube.h[0], cube.h[1]); glVertex2f(cube.e[0], cube.e[1]);

        glVertex2f(cube.a[0], cube.a[1]); glVertex2f(cube.e[0], cube.e[1]);
        glVertex2f(cube.b[0], cube.b[1]); glVertex2f(cube.f[0], cube.f[1]);
        glVertex2f(cube.c[0], cube.c[1]); glVertex2f(cube.g[0], cube.g[1]);
        glVertex2f(cube.d[0], cube.d[1]); glVertex2f(cube.h[0], cube.h[1]);
    glEnd();
}

// Callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) { // Se a tecla for pressionada
        switch (key) {
            // Troca o triângulo atual pelo escalado se for pressionado B
            case GLFW_KEY_B:
                cube = scaledCube;
                break;
            // Troca o triângulo atual pelo com composição se for pressionado D
            case GLFW_KEY_D:
                cube = compositionCube;
                break;
            // Se a tecla for ESC chama a função que fecha a janela se for pressionado ESC
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) { // Se a tecla for solta
        cube = cubeInit; // Volta ao triângulo inicial
    }
}

int main() {
    if (!glfwInit()) return -1; // Irá iniciaar a biblioteca e verificar se foi iniciada corretamente

    // Irá criar e definir a janela, sua resolução, titulo e etc...
    GLFWwindow* window = glfwCreateWindow(1024, 576, "Cube Transformations", NULL, NULL);
    // Irá verificar ser a janela foi criada corretamente
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Irá apresentar a janela no contexto atual e as cores do background
    glfwMakeContextCurrent(window);
    glClearColor(0.1, 0.1, 0.1, 1);

    // Configura o callback de teclado
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderiza o triângulo atual
        glColor3f(0.0f, 1.0f, 1.0f);
        renderCube(cube);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
