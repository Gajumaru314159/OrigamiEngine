#pragma once
#include <memory>

namespace OrigamiGraphic
{
	enum class DX_VERSION {
		DX12
	};

	class IDXWrapper
	{
	public:
		virtual void Delete() { delete this; };


		virtual int Init() = 0;
		
		virtual int SwapScreen()=0;

		virtual int LoadGraph(const String& path)=0;
	};
}

namespace std
{
	template<>
	struct default_delete<OrigamiGraphic::IDXWrapper>
	{
		void operator()(OrigamiGraphic::IDXWrapper* p) const
		{
			p->Delete();
		}
	};
};