/*************************************************
 * @file Atv1/main.cpp
 * @author Pedro Augusto Sousa Gonçalves - 21.1.4015
 * @brief Esse arquivo é para a segunda Atividade
*************************************************/

#include <GLFW/glfw3.h>

/**************************************************************************************
 *@brief Uma aplicação que aplique interatividade com a bibliotecas OpenGL
 * 
 * Para fazer a aplicação que aplique interatividade irei ultilizar a biblioteca GLFW que
 * ultiliza o OpenGL, OpenGl ES e Vulkan. Eu a escolhi por ser mais simples, rapida e ter
 * suporte ao Wayland. A aplicação será apresentar uma tela com o nome "Troca de cor" e
 * que mudaraá para Vermelho se for clicado "R", Azul se for clicado "B" e Verde se for
 * clicado "G", "ESC" irá fechar a janela.
**************************************************************************************/

/// Cada cor será representada por uma variavel global
float red = 0.55f, green = 0.0f, blue = 0.9f;

/// É declarado a função que ira definir uma respota para cada entrada
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) { /// Verifica se alguma tecla foi precionada
        switch (key) {
            case GLFW_KEY_R: /// Se a tecla for R coloca 1 para o pigmeto verlho e 0 para os outros
                red = 1.0f; green = 0.0f; blue = 0.0f;
                break;
            case GLFW_KEY_G: /// Se a tecla for G coloca 1 para o pigmeto verde e 0 para os outros
                red = 0.0f; green = 1.0f; blue = 0.0f;
                break;
            case GLFW_KEY_B: /// Se a tecla for G coloca 1 para o pigmeto azul e 0 para os outros
                red = 0.0f; green = 0.0f; blue = 1.0f;
                break;
            case GLFW_KEY_ESCAPE: /// Se a tecla for ESC chama a função que fecha a janela
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    }
}

int main() {
    if (!glfwInit()) return -1; /// Irá iniciaar a biblioteca e verificar se foi iniciada corretamente

    /// Irá criar e definir a janela, sua resolução, titulo e etc...
    GLFWwindow* window = glfwCreateWindow(800, 600, "Troca de Cor", nullptr, nullptr);
    
    /// Irá verificar ser a janela foi criada corretamente
    if (!window){
        glfwTerminate();
        return -1;
    }

    /// Irá apresentar a janela no contexto atual
    glfwMakeContextCurrent(window);

    /// Atribui a função de atribuição das entradas à janela que foi criada
    glfwSetKeyCallback(window, key_callback);


    while (!glfwWindowShouldClose(window)) {
        /// Muda a cor da janela
        glClearColor(red, green, blue, 1.0f);

        /// Renderiza a janela
        glClear(GL_COLOR_BUFFER_BIT);
        
        /// Trocar os buffers back e front
        glfwSwapBuffers(window);

        /// Sobe os eventos processados, mas como não é passado nada como parametro, nada será passado 
        glfwPollEvents();
    }
    
    /// Termina o uso da biblioteca
    glfwTerminate();
    return 0;
}
