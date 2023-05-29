#include <NettEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include "glm/ext/matrix_transform.inl"
#include "glm/gtc/type_ptr.inl"

class ExampleLayer : public NettEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f)
	{
		m_VertexArray.reset(NettEngine::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		NettEngine::Ref<NettEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(NettEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		NettEngine::BufferLayout layout = {
			{NettEngine::ShaderDataType::Float3, "a_Position"},
			{ NettEngine::ShaderDataType::Float2, "a_TexCoord" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		NettEngine::Ref<NettEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(NettEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

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

		m_FlatColorShader.reset(NettEngine::Shader::Create(vertexSrc, fragmentSrc));


		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(NettEngine::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = NettEngine::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<NettEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<NettEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(NettEngine::Timestep ts) override
	{
		ProcessCameraInput(ts);

		NettEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		NettEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		NettEngine::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<NettEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<NettEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		const glm::vec3 pos(-0.5f);
		const glm::mat4 transform = glm::translate(glm::mat4(1.f), pos);

		NettEngine::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform);

		m_Texture->Bind();
		NettEngine::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		NettEngine::Renderer::EndScene(); 
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(NettEngine::Event& event) override
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
	NettEngine::Ref<NettEngine::Shader> m_FlatColorShader, m_TextureShader;
	NettEngine::Ref<NettEngine::VertexArray> m_VertexArray;

	NettEngine::Ref<NettEngine::Texture2D> m_Texture;

	NettEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.f;

	float m_CameraRotation = 0.f;
	float m_CameraRotationSpeed = 90.f;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.f };
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