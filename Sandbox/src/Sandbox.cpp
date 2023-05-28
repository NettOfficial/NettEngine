#include <NettEngine.h>

#include "imgui/imgui.h"
#include "glm/ext/matrix_transform.inl"

class ExampleLayer : public NettEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f)
	{
		m_VertexArray.reset(NettEngine::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f, 1.f,
			0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.f,
			0.f, 0.5f, 0.f, 1.f, 1.f, 0.f, 1.f
		};
		std::shared_ptr<NettEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(NettEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		NettEngine::BufferLayout layout = {
			{NettEngine::ShaderDataType::Float3, "a_Position"},
			{NettEngine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<NettEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(NettEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			uniform vec4 u_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = u_Color;
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
				color = v_Color;
			}
		)";

		m_Shader.reset(new NettEngine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(NettEngine::Timestep ts) override
	{
		ProcessCameraInput(ts);

		NettEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		NettEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		NettEngine::Renderer::BeginScene(m_Camera);

		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.f);
		glm::vec4 redColor(0.8f, 0.3f, 0.2f, 0.5f);

		glm::vec3 pos(-0.5f);
		glm::mat4 transform = glm::translate(glm::mat4(1.f), pos);

		m_Shader->UploadUniformFloat4("u_Color", blueColor);
		NettEngine::Renderer::Submit(m_Shader, m_VertexArray);

		m_Shader->UploadUniformFloat4("u_Color", redColor);
		NettEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);

		NettEngine::Renderer::EndScene();
	}
	void OnImGuiRender() override
	{
		
	}

	void OnEvent(NettEngine::Event& event) override
	{
		
	}

	void ProcessCameraInput(NettEngine::Timestep ts)
	{
		if (NettEngine::Input::IsKeyPressed(NE_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		else if (NettEngine::Input::IsKeyPressed(NE_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}

		if (NettEngine::Input::IsKeyPressed(NE_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		} 
		else if (NettEngine::Input::IsKeyPressed(NE_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}

		if (NettEngine::Input::IsKeyPressed(NE_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (NettEngine::Input::IsKeyPressed(NE_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
	}

private:
	std::shared_ptr<NettEngine::Shader> m_Shader;
	std::shared_ptr<NettEngine::VertexArray> m_VertexArray;

	NettEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.f;

	float m_CameraRotation = 0.f;
	float m_CameraRotationSpeed = 90.f;
};

class Sandbox : public NettEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

NettEngine::Application* NettEngine::CreateApplication()
{
	return new Sandbox();
}