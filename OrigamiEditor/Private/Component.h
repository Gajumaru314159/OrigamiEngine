/**
* pfile Component.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine {
	namespace GUILayout {
		/**
		* @brief �G�f�B�^�[��GUI���\������R���|�[�l���g�̃N���X�B
		*/
		class Component
		{
		public:
			/**
			* @brief �R���|�[�l���g�B
			*/
			Component();


			/**
			* @brief �`��Ə����̍X�V�B
			*/
			virtual void update() = 0;

			/**
			* @brief �`��Ə����̍X�V�����s���邩��ݒ�B
			* @param flag �t���O�Btrue���ƕ`�揈�����L���ɂȂ�B
			*/
			void SetEnable(bool flag);

			/**
			* @brief �R���|�[�l���g�̍ŏ��T�C�Y��ݒ�B
			*/
			void SetMinimumSize(U32 width, U32 height);

			/**
			* @brief �R���|�[�l���g�̍ő�T�C�Y��ݒ�B
			*/
			void SetMaximumSize(U32 width, U32 height);


			/**
			* @brief �R���|�[�l���g�̉������擾�B
			* @return �R���|�[�l���g�̉����B
			*/
			U32 GetWidth();

			/**
			* @brief �R���|�[�l���g�̍������擾�B
			* @return �R���|�[�l���g�̍����B
			*/
			U32 GetHeight();
		private:
			// �`�揈�����L����
			bool m_IsEnable;

			// �R���|�[�l���g�̉���
			U32 m_Width;
			// �R���|�[�l���g�̍���
			U32 m_Height;

			// �R���|�[�l���g�̍ŏ��̉���
			U32 m_MinWidth;
			// �R���|�[�l���g�̍ŏ��̍���
			U32 m_MinHeight;

			// �R���|�[�l���g�̍ő�̉���
			U32 m_MaxWidth;
			// �R���|�[�l���g�̍ő�̍���
			U32 m_MaxHeight;
		};
	}
}