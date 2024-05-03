#pragma once

#include "Fanatic/Layer.h"

#include "Fanatic/Events/ApplicationEvent.h"
#include "Fanatic/Events/KeyEvent.h"
#include "Fanatic/Events/MouseEvent.h"

namespace Fanatic {

	class FANATIC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttack() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}