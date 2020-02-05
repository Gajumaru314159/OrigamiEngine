#pragma once

#include "Container.h"

#include <vector>
#include <memory>

#include "ITab.h"



namespace OrigamiEngine {
	class TabContainer :public Container
	{
	public:
		~TabContainer();

		void Draw(const S32 x, const S32 y, const S32 width, const S32 height)override;
		bool AddTab(ITab* tab, const U32 index = -1)override;
	private:
		ArrayList<UPtr<ITab>> m_Tabs;
		S32 m_ActiveIndex;
	};

}