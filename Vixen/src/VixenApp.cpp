#include <Fanatic.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Fanatic::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Fanatic::VertexArray::Create());					// Triangle Vertices

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			-0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Fanatic::Ref<Fanatic::VertexBuffer> vertexbuffer;
		vertexbuffer.reset(Fanatic::VertexBuffer::Create(vertices, sizeof(vertices)));
		Fanatic::BufferLayout layout = {
			{ Fanatic::ShaderDataType::Float3, "a_Position" },
			{ Fanatic::ShaderDataType::Float4, "a_Color" }
		};
		vertexbuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexbuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Fanatic::Ref<Fanatic::IndexBuffer> indexbuffer;
		indexbuffer.reset(Fanatic::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexbuffer);

		m_SquareVA.reset(Fanatic::VertexArray::Create());

		float squareVertices[5 * 4] = {											// Square Vertices
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Fanatic::Ref<Fanatic::VertexBuffer> squareVB;
		squareVB.reset(Fanatic::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Fanatic::ShaderDataType::Float3, "a_Position" },
			{ Fanatic::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Fanatic::Ref<Fanatic::IndexBuffer> squareIB;
		squareIB.reset(Fanatic::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Fanatic::Shader::Create(vertexSrc, fragmentSrc));

		Shader::Create("assets/shaders/Texture.glsl");

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4 (u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Fanatic::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Fanatic::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Fanatic::Texture2D::Create("assets/textures/Checkerboard.png");
		m_FanaticLogoTexture = Fanatic::Texture2D::Create("assets/textures/FanaticLogo.png");

		std::dynamic_pointer_cast<Fanatic::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Fanatic::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Fanatic::Timestep ts) override
	{
		if (Fanatic::Input::IsKeyPressed(FNC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Fanatic::Input::IsKeyPressed(FNC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Fanatic::Input::IsKeyPressed(FNC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Fanatic::Input::IsKeyPressed(FNC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Fanatic::Input::IsKeyPressed(FNC_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Fanatic::Input::IsKeyPressed(FNC_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Fanatic::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fanatic::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotaion(m_CameraRotation);

		Fanatic::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Fanatic::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Fanatic::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Fanatic::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Fanatic::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_FanaticLogoTexture->Bind();
		Fanatic::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Fanatic::Renderer::Submit(m_Shader, m_VertexArray);
		
		Fanatic::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Fanatic::Event& event) override
	{
	}
private:
	Fanatic::Ref<Fanatic::Shader> m_Shader;
	Fanatic::Ref<Fanatic::VertexArray> m_VertexArray;

	Fanatic::Ref<Fanatic::Shader> m_FlatColorShader, m_TextureShader;
	Fanatic::Ref<Fanatic::VertexArray> m_SquareVA;

	Fanatic::Ref<Fanatic::Texture2D> m_Texture, m_FanaticLogoTexture;

	Fanatic::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation= 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Vixen : public Fanatic::Application
{
public:
	Vixen()
	{
		PushLayer(new ExampleLayer());
	}

	~Vixen()
	{

	}

};

Fanatic::Application* Fanatic::CreateApplication()
{
	return new Vixen();
}