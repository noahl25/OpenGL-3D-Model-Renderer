#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Debug.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


int main(void) {

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480,  "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cerr <<  "glew failed to initialize" << std::endl;


    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f
        };

        unsigned indicies[] = {
            0, 1, 2,
            2, 3, 0
        };
 
        IndexBuffer ib(indicies, 6);

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

        glm::mat4 mvp = proj * view * model;

        Shader shader("Shader.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", { 1.0f, 0.0f, 0.0f, 1.0f });
        
        VertexArray va;
        va.AddBuffer(vb, layout);
        va.AddIndexBuffer(ib);

        Texture texture("Test.png");
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;

        glm::vec3 translation(200, 200, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            model = glm::translate(glm::mat4(1.0f), translation);
            mvp = proj * view * model;
            

            shader.SetUniformMat4("u_MVP", mvp);


            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();


            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 640.0f); 
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
 
            shader.SetUniformMat4("u_MVP", mvp);
            renderer.Draw(va, shader);

            model = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x + 100, translation.y + 100, translation.z));
            mvp = proj * view * model;

            shader.SetUniformMat4("u_MVP", mvp);
            renderer.Draw(va, shader);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }

    }

    glfwTerminate();
    return 0;
}