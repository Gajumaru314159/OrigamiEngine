#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	class GUID
	{
	public:
		GUID();
		GUID(String str);

		/**
		* @brief �f�[�^�𕶎���Ƃ��Ď��o���B"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"�`��
		* @return String�`����GUID
		*/
		String ToString();

		// ��r���Z�q
		bool operator==(const GUID& an);
		bool operator!=(const GUID& an);

	private:
		U32 a,b,c,d;
	};
}