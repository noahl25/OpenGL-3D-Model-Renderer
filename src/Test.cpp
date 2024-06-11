#include "Test.h"

#include <fstream>
#include <sstream>

#include <Windows.h>
#include <mmsystem.h>

#include "Timer.h"
#include "Input.h"

#define M_PI           3.14159265358979323846
#define RADIANS(x) (float)((x) * M_PI / 180)

/*clear color*/

test::TestClearColor::TestClearColor() 
	: m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

test::TestClearColor::~TestClearColor()
{
	glClearColor(0, 0, 0, 255);
}

void test::TestClearColor::OnUpdate(float deltaTime)
{
}

void test::TestClearColor::OnRender()
{
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
}

/*test menu*/

test::TestMenu::TestMenu(Test*& currentTestPtr)
	: m_CurrentTest(currentTestPtr)
{
}

void test::TestMenu::OnImGuiRender()
{
	for (auto& test : m_Tests) {
		if (ImGui::Button(test.first.c_str())) {
			m_CurrentTest = test.second();
		}
	}
}

/*texture 2d*/

test::TextureTest2D::TextureTest2D()
    : m_Shader("Shader.shader"), m_Texture("Test.png")
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

    m_IndexBuffer = new IndexBuffer(indicies, 6);

    m_VertexBuffer = new VertexBuffer(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    m_Shader.Bind();
    m_Shader.SetUniform4f("u_Color", { 1.0f, 0.0f, 0.0f, 1.0f });

    m_VAO.AddBuffer(*m_VertexBuffer, layout);
    m_VAO.AddIndexBuffer(*m_IndexBuffer);

    m_Texture.Bind(0);
    m_Shader.SetUniform1i("u_Texture", 0);
}

test::TextureTest2D::~TextureTest2D()
{
    delete m_IndexBuffer;
    delete m_VertexBuffer;
}

void test::TextureTest2D::OnUpdate(float deltaTime)
{
}

void test::TextureTest2D::OnRender()
{
    Renderer renderer;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

    glm::mat4 mvp = proj * view * model;

    m_Shader.SetUniformMat4("u_MVP", mvp);

    renderer.Draw(m_VAO, m_Shader);
}

void test::TextureTest2D::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 640.0f);
}

/*projection 3d*/

test::ModelRendererTest::ModelRendererTest()
    : m_ModelRenderer("VerySmoothMonkey.txt"), m_Shader("Shader.shader")
{

 
}

test::ModelRendererTest::~ModelRendererTest()
{
 
}

void test::ModelRendererTest::OnUpdate(float deltaTime)
{
    cam.Update(deltaTime);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view;
    view = cam.GetViewMatrix();

    glm::mat4 projection;
    projection = cam.GetProjectionMatrix();

    m_Shader.SetUniformMat4("u_Model", model);
    m_Shader.SetUniformMat4("u_View", view);
    m_Shader.SetUniformMat4("u_Projection", projection);
}

void test::ModelRendererTest::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_ModelRenderer.Render();
}

void test::ModelRendererTest::OnImGuiRender()
{
}
 

/*vertex test*/

test::VertexTest::VertexTest()
    : m_Shader("Shader.shader"), m_Texture("Container.jpg"), m_Texture1("awesomeface.png")
{
 
    
 

 

//float vertices[] = {
//-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//};
//
//
//unsigned indicies[] = {
//    0, 1, 2,
//    2, 3, 0
//};

    MeshData data = parseObj("SmoothMonkey.txt");

    m_VertexBuffer = new VertexBuffer(data.vertexPositions.data(), data.vertexPositions.size() * sizeof(float));
    m_IndexBuffer = new IndexBuffer(data.indicies.data(), data.indicies.size());

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(4);

    m_Shader.Bind();

    m_VAO.AddBuffer(*m_VertexBuffer, layout);
    m_VAO.AddIndexBuffer(*m_IndexBuffer);


    m_Texture1.Bind(1);
    m_Shader.SetUniform1i("u_Texture1", 1);

    m_Texture.Bind(0);
    m_Shader.SetUniform1i("u_Texture", 0);
 
}

test::VertexTest::~VertexTest()
{
}

void test::VertexTest::OnUpdate(float deltaTime)
{

    cam.Update(deltaTime);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view;
    view = cam.GetViewMatrix();
 

    glm::mat4 projection;
    projection = cam.GetProjectionMatrix();

    m_Shader.SetUniformMat4("u_Model", model);
    m_Shader.SetUniformMat4("u_View", view);
    m_Shader.SetUniformMat4("u_Projection", projection);

}

void test::VertexTest::OnRender()
{
//    glm::vec3 cubePositions[] = {
//glm::vec3(0.0f, 0.0f, 0.0f),
//glm::vec3(2.0f, 5.0f, -15.0f),
//glm::vec3(-1.5f, -2.2f, -2.5f),
//glm::vec3(-3.8f, -2.0f, -12.3f),
//glm::vec3(2.4f, -0.4f, -3.5f),
//glm::vec3(-1.7f, 3.0f, -7.5f),
//glm::vec3(1.3f, -2.0f, -2.5f),
//glm::vec3(1.5f, 2.0f, -2.5f),
//glm::vec3(1.5f, 0.2f, -1.5f),
//glm::vec3(-1.3f, 1.0f, -1.5f)
//    };
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_VAO.Bind();
    Renderer renderer;
    renderer.Draw(m_VAO, m_Shader);

//for (int i = 0; i < 10; i++) {
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, cubePositions[i]);
//    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) * i, glm::vec3(0.5f, 1.0f, 0.0f));
//    m_Shader.SetUniformMat4("u_Model", model);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//}

}

void test::VertexTest::OnImGuiRender()
{
}


static int fastrand(int g_seed) {
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

test::VertexTest::MeshData test::VertexTest::parseObj(const char* path)
{
    Timer t("Loading");
    MeshData data;

    std::ifstream stream(path);
    std::string line;

    srand(time(NULL));
    int counter = 1;
    while (std::getline(stream, line)) {

        if (line[0] == 'v' && line[1] == ' ') {
            line = line.substr(2);
            std::stringstream ss(line);
 
            float num;
            while (ss >> num) {
                data.vertexPositions.push_back(num);
            }
 
            data.vertexPositions.push_back(0.2 + counter / 10000);
            counter = fastrand(counter);
            data.vertexPositions.push_back(0.2 + counter / 10000);
            counter = fastrand(counter);
            data.vertexPositions.push_back(0.2 + counter / 10000);
            data.vertexPositions.push_back(1.0f);
        }

        if (line[0] == 'f' && line[1] == ' ') {
            line = line.substr(2);
            std::stringstream parse(line);
            std::string section;
            std::vector<int> temp;
            while (std::getline(parse, section, ' ')) {
                temp.push_back(std::stoi(section.substr(0, section.find('/'))) - 1);
            }

            if (temp.size() == 4) {

                data.indicies.push_back(temp[0]);
                data.indicies.push_back(temp[1]);
                data.indicies.push_back(temp[2]);

                data.indicies.push_back(temp[0]);
                data.indicies.push_back(temp[2]);
                data.indicies.push_back(temp[3]);

            }

            else if (temp.size() == 3) {
                data.indicies.push_back(temp[0]);
                data.indicies.push_back(temp[1]);
                data.indicies.push_back(temp[2]);
            }

            else {
                std::cout << "Unkown case: " << temp.size() << std::endl;
                ASSERT(false);
            }

        }

        counter = fastrand(counter);
    }
 
    return data;
}
