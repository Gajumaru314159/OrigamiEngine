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

		void Draw(const F32 x, const F32 y, const F32 width, const F32 height)override;
		bool AddTab(ITab* tab, const U32 index = -1)override;
		void AddContainer(std::unique_ptr<Container>&& container, float endPercentage);
		void SetIsVertical(bool isVertival);
	private:
		std::vector<std::unique_ptr<Container>> m_Containers;
		int m_ActiveIndex;
		bool m_IsVertical;
		bool m_IsDragging;
		int m_DragIndex;
	};

}