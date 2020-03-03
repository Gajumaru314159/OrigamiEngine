/**
* @file Container.h
*/
#pragma once
#include "OrigamiAPI.h"
#include "ITab.h"



namespace OrigamiEngine {
	/**
	* @brief �^�u��ێ����邱�Ƃ̂ł���R���e�i�B
	*/
	class Container {
	public:
		virtual ~Container() {}

		/**
		* @brief �R���e�i�̕ێ�����q�v�f�̐����擾����B
		* @return �q�v�f�̐��B
		*/
		virtual U32 GetChildCount() { return 0; };

		/**
		* @brief �R���e�i�̕`��B
		* @param x �`��ʒuX
		* @param y �`��ʒuY
		* @param width �`�敝
		* @param height �`�捂
		*/
		virtual void Draw(const S32 x, const S32 y, const S32 width, const S32 height)=0;

		virtual bool AddTab(ITab* tab, const U32 index = -1)=0;

		float GetPercentage();
		void SetPercentage(const float percentage);
	private:
		float m_Percentage = 0;
	};
}