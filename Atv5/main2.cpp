#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>

typedef std::array<float, 3> point;

struct Quad {
    point a, b, c, d;
};

point multiplyMatrixVector(const std::vector<std::vector<float>>& matrix, const point& vec) {
    point result = {0,0,0};

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

Quad quad = {
    {-0.05f, -0.05f, 1.0f}, 
    {0.05f, -0.05f, 1.0f},
    {0.05f, 0.05f, 1.0f},
    {-0.05f, 0.05f, 1.0f}, 
};


void renderQuad(const Quad& in) {

    glBegin(GL_LINES);
        glVertex2d(in.a[0], in.a[1]); glVertex2d(in.b[0], in.b[1]);
        glVertex2d(in.b[0], in.b[1]); glVertex2d(in.c[0], in.c[1]);
        glVertex2d(in.c[0], in.c[1]); glVertex2d(in.d[0], in.d[1]);
        glVertex2d(in.d[0], in.d[1]); glVertex2d(in.a[0], in.a[1]);
    glEnd();
}

Quad convert(float dx, float dy, Quad in){
    return {
        translation2D(dx, dy, in.a),
        translation2D(dx, dy, in.b),
        translation2D(dx, dy, in.c),
        translation2D(dx, dy, in.d),
    };
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                quad = convert(0, 0.05, quad);
                break;
            case GLFW_KEY_DOWN:
                quad = convert(0, -0.05, quad);
                break;
            case GLFW_KEY_LEFT:
                quad = convert(-0.05, 0, quad);
                break;
            case GLFW_KEY_RIGHT:
                quad = convert(0.05, 0, quad);
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1024, 1024, "Cube Transformations", NULL, NULL);
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
        renderQuad(quad);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}