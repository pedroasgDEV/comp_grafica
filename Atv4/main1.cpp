#include <GLFW/glfw3.h>

// Função para desenhar o gradiente RGB
void drawGradient() {
    glBegin(GL_QUADS);

        // Desenha o gradiente horizontalmente, alterando o vermelho (R)
        for (int x = 0; x < 256; ++x) {
            float r = x / 255.0f; // Valor normalizado de R (0 a 1)
            float xpos = -1.0f + 2.0f * (x / 255.0f); // Converte para coordenadas NDC

            // Desenha uma faixa vertical de largura 1 pixel
            glColor3f(r, 0.0f, 0.0f); // Define cor (R, G, B)
            glVertex2f(xpos, -1.0f);  // Ponto inferior esquerdo
            glVertex2f(xpos + 0.01f, -1.0f);  // Ponto inferior direito
            glVertex2f(xpos + 0.01f, 1.0f);   // Ponto superior direito
            glVertex2f(xpos, 1.0f);   // Ponto superior esquerdo
        }

    glEnd();
}

int main() {
    if (!glfwInit()) return -1; // Irá iniciaar a biblioteca e verificar se foi iniciada corretamente

    // Irá criar e definir a janela, sua resolução, titulo e etc...
    GLFWwindow* window = glfwCreateWindow(1024, 576, "RGB Gradient", NULL, NULL);
    // Irá verificar ser a janela foi criada corretamente
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /// Irá apresentar a janela no contexto atual e as cores do background
    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo preto

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        drawGradient(); // Chama a função para desenhar o gradiente

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
