#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	class Tab
	{
	public:
		virtual void OnGUI()=0;

		String GetTabName();

		void SetRect(const I32 top, const I32 bottom, const I32 left, const I32 right);

		/*void BeginBox();
		void EndBox();*/
		bool PlaceButton();

		/**
		* @brief �w�肵���X�L���̃{�^����z�u
		* @return �{�^����������Ă����true��Ԃ�
		*/
		/*bool PlaceRepeatButton();
		void PlaceSpace();
		bool PlaceToggle();
		String PlaceTextField();
		String PlaceTextArea();*/
		// �X�N���[���o�[

	protected:
		String m_TabName = L"No Name";
	private:
		Rect m_TabRect;
		I32 m_Y;
	};
}