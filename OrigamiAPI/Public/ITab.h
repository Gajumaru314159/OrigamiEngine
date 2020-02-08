#pragma once

#include "OrigamiAPI.h"
#include "ITabBuilder.h"

namespace OrigamiEngine {
	class ITab
	{
	public:
		String GetTabName() { return m_TabName; };

		virtual void OnGUI(ITabBuilder& tabBuilder) = 0;

		virtual ITab* CreateInstance()=0;

		virtual void Delete() { delete this; };
	protected:
		String m_TabName = L"No Name";
	private:
		Rect m_TabRect;
		S32 m_Y;
	};
}


namespace std
{
	template<>
	struct default_delete<OrigamiEngine::ITab>
	{
		void operator()(OrigamiEngine::ITab* p) const
		{
			p->Delete();
		}
	};
};