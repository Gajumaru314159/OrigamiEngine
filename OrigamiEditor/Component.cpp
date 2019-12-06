#include "Component.h"

/**
* pfile Component.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine {
	namespace GUILayout {
		Component::Component() :
			m_IsEnable(true),
			m_Width(0),
			m_Height(0)
		{
			SetMinimumSize(0, 0);
			SetMaximumSize(0, 0);
		}
		void Component::SetEnable(bool flag)
		{
			m_IsEnable = flag;
		}

		void Component::SetMinimumSize(U32 width, U32 height)
		{
			m_MinWidth = width;
			m_MinHeight = height;
		}

		void Component::SetMaximumSize(U32 width, U32 height)
		{
			m_MaxWidth = width;
			m_MaxHeight = height;
		}

		U32 Component::GetWidth()
		{
			return m_Width;
		}

		U32 Component::GetHeight()
		{
			return m_Height;
		}
	}
}