#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class UUID
	{
	public:
		UUID();
		UUID(String str);

		/**
		* @brief �f�[�^�𕶎���Ƃ��Ď��o���B"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"�`��
		* @return String�`����UUID
		*/
		String ToString();

		// ��r���Z�q
		bool operator==(const UUID& an);
		bool operator!=(const UUID& an);

	private:
		U32 a,b,c,d;
	};
}