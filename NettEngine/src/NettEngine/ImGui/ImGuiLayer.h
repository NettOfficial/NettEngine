#pragma once

#include "NettEngine/Layer.h"

#include "NettEngine/Events/KeyEvent.h"
#include "NettEngine/Events/MouseEvent.h"
#include "NettEngine/Events/ApplicationEvent.h"

namespace NettEngine
{
	class NETTENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0;

	};

}