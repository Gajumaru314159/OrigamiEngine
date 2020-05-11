/**
* @file Allocator.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine
{
	/**
	* @brief �v�[���A���P�[�^
	* @details �����������炩���ߊm�ۂ��Ă����A��ʂ��؂�o���Ċ��蓖�ĂĂ����B������������Ȃ��ꍇ�̓�������Ԃ�{�ɂ���B
	*/
	class Allocator
	{
	public:
		/**
		* @brief �R���X�g���N�^�B
		* @param blockSize ���蓖�Ă邱�Ƃ̂ł���u���b�N�̍ő�T�C�Y�B�ŏ��l��4�o�C�g�B�����l��64�o�C�g�B
		* @param ���蓖�Ă邱�Ƃ̂ł��u���b�N�̐��B�����l��1024�B
		*/
		Allocator(U32 blockSize=64,U32 blockNum=1024);
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&)=delete;

		virtual ~Allocator();

		/**
		* @brief �w�肵���T�C�Y�̃�������ǉ��Ŋm�ۂ���B
		* @param blockNum �m�ۂ���u���b�N�̐��B0�̏ꍇ���݊m�ۂ���Ă���u���b�N�Ɠ������m�ۂ���B
		*/
		void AddBlock(U32 blockNum=1);


		/**
		* @brief �������̊��蓖�ėv���B
		* @details �w�肵���^�T�C�Y���u���b�N�T�C�Y�ȉ��Ȃ玖�O�Ɋm�ۂ������������犄�蓖�Ă��A�ȏ�Ȃ�null��Ԃ��B
		*/
		void* pnew(U32 size);

		/**
		* @brief �m�ۂ�����������ԋp����B
		* @details �ԋp����ƃ������̏��L�����Ȃ��Ȃ胁�����̒l�͖���`�ƂȂ�B�܂��Ǌ��O�̃|�C���^��n�����ꍇ������`�ƂȂ�B
		* @param �ԋp���郁�����̃|�C���^
		*/
		void pdel(void*& ptr);



		U32 GetBlockSize()const;

	private:

		/**
		* @brief �m�ۂ����������̃|�C���^�ƃT�C�Y���Ǘ�
		*/
		struct Header
		{
			void* ptr=nullptr;
			U32 size=0;
		};



		// ���蓖�Ă邱�Ƃ̂ł���u���b�N�̍ő�T�C�Y�B
		U32 m_BlockSize;
		// ���蓖�Ă邱�Ƃ̂ł���u���b�N�̐��B
		U32	m_TotalBlockNum;

		// �Ǝ��Ɋ��蓖�Ă郁������Ԃ̃|�C���^�B
		ArrayList<Header> m_MemoryList;


		// ���蓖�ĉ\�ȃ������u���b�N�̃X�^�b�N�B
		Stack<void*> m_AllocatablePtr;
	};
}