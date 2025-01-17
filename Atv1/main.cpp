/*************************************************
 * @file Atv1/main.cpp
 * @author Pedro Augusto Sousa Gonçalves - 21.1.4015
 * @brief Esse arquivo é para a primeira Atividade
*************************************************/

#include <GLFW/glfw3.h>

/**************************************************************************************
 *@brief Uma aplicação basica com a bibliotecas OpenGL
 * 
 * Para fazer a aplicação basica irei ultilizar a biblioteca GLFW que ultiliza o OpenGL,
 * OpenGl ES e Vulkan. Eu a escolhi por ser mais simples, rapida e ter suporte ao Wayland.
 * A aplicação será apresentar uma tela com o nome "Hello World" e com o fundo roxo.
**************************************************************************************/

int main(void)
{   

    if (!glfwInit()) return -1; /// Irá iniciaar a biblioteca e verificar se foi iniciada corretamente

    /// Irá criar e definir a janela, sua resolução, titulo e etc...
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    /// Irá verificar ser a janela foi criada corretamente
    if (!window){
        glfwTerminate();
        return -1;
    }

    /// Irá apresentar a janela no contexto atual
    glfwMakeContextCurrent(window);

    /// Irá definir a cor de fundo da tela, aqui sera roxo 
    glClearColor(0.55, 0, .90, 1);

    /// Esse looping ficará ativo enquanto a janelar não for fechada
    while (!glfwWindowShouldClose(window))
    {
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

/**************************************************************************************
 *@brief Resultados
 * 
 * Para fazer a aplicação basica irei ultilizar a biblioteca GLFW que ultiliza o OpenGL,
 * OpenGl ES e Vulkan. Eu a escolhi por ser mais simples, rapida e ter suporte ao Wayland.
 * A aplicação será apresentar uma tela com o nome "Hello World" e com o fundo roxo.
**************************************************************************************/