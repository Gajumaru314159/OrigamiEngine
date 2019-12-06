#pragma once

#include "Container.h"

#include <vector>
#include <memory>

#include "Tab.h"



namespace OrigamiEngine {
	class TabContainer :public Container
	{
	public:
		~TabContainer();

		void Draw(const int x, const int y, const int width, const int height)override;
		void AddTab(std::unique_ptr<Tab>&& tab, const unsigned int index = -1);
	private:
		std::vector<std::unique_ptr<Tab>> m_Tabs;
		int m_ActiveIndex;
	};

}