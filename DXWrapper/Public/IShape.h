#pragma once
#include "IDeletable.h"
namespace og
{
	class IShape :public IDeletable
	{
	public:
		virtual S32 Vertex(const Byte* bytes,const U32 size)=0;
		virtual S32 Indices(const U32 index1, const U32 index2, const U32 index3) = 0;
		virtual S32 Indices(const U32* indices,const U32 count)=0;

		virtual S32 GetStribeSize() = 0;
		virtual S32 GetVertexCount() = 0;
		virtual S32 GetIndexCount() = 0;
	};
}