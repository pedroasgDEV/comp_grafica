#include <GLFW/glfw3.h>
#include <vector>
#include <array>

typedef std::array<float, 4> point;

struct Cube {
    point a, b, c, d, e, f, g, h;
};

point multiplyMatrixVector(const std::vector<std::vector<float>>& matrix, const point& vec) {
    point result = {0.0f, 0.0f, 0.0f, 0.0f};
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < vec.size(); j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

point translation3D(float dx, float dy, float dz, const point& a) {
    std::vector<std::vector<float>> translationMatrix = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    return multiplyMatrixVector(translationMatrix, a);
}

point scale3D(float sx, float sy, float sz, const point& a) {
    std::vector<std::vector<float>> scaleMatrix = {
        {sx, 0,  0,  0},
        {0,  sy, 0,  0},
        {0,  0,  sz, 0},
        {0,  0,  0,  1}
    };
    return multiplyMatrixVector(scaleMatrix, a);
}

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

Cube cube = cubeInit;

point project3DTo2D(const point& a, float focalLength = 1) {
    float factor = focalLength / (a[2] + 1.0f);
    return {a[0] * factor, a[1] * factor, 0.0f, 1.0f};
}

void renderCube(const Cube& in) {
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_B:
                cube = scaledCube;
                break;
            case GLFW_KEY_D:
                cube = compositionCube;
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) {
        cube = cubeInit;
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1024, 576, "Cube Transformations", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.1, 0.1, 0.1, 1);


    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0f, 1.0f, 1.0f);
        renderCube(cube);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
