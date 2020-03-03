#pragma once

#include "Container.h"

#include <memory>
#include <vector>



namespace OrigamiEngine {

	class SplitContainer :public Container
	{
	public:
		SplitContainer() :m_ActiveIndex(0),m_IsVertical(true),m_IsDragging(false), m_DragIndex(-1){};
		~SplitContainer()override;

		void Draw(const S32 x, const S32 y, const S32 width, const S32 height)override;
		bool AddTab(ITab* tab, const U32 index = -1)override;
		void AddContainer(std::unique_ptr<Container>&& container, float endPercentage);
		void SetIsVertical(bool isVertival);
	private:
		std::vector<std::unique_ptr<Container>> m_Containers;
		S32 m_ActiveIndex;
		bool m_IsVertical;
		bool m_IsDragging;
		S32 m_DragIndex;
	};

}