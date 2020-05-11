#include "pch.h"
#include "Allocator.h"

namespace OrigamiEngine
{
	Allocator::Allocator(U32 blockSize, U32 blockNum) :
		m_BlockSize(blockSize),
		m_TotalBlockNum(0)
	{
		if (blockSize <= 4)blockSize = 4;
		AddBlock(blockSize);
	}

	Allocator::~Allocator()
	{
		for (auto& header : m_MemoryList)
		{
			free(header.ptr);
		}
	}


	void Allocator::AddBlock(U32 blockNum) 
	{
		if (blockNum == 0)blockNum = m_TotalBlockNum;

		// �q�[�v�̈悩�烁�����̊m��
		Byte* ptr = (Byte*)malloc((size_t)m_BlockSize * blockNum);

		Header header;
		header.ptr = ptr;
		header.size = blockNum;

		m_MemoryList.push_back(header);

		// ���蓖�ĉ\�ȃ������u���b�N��ۑ�
		for (U32 i = 0;i < blockNum;i++)
		{
			m_AllocatablePtr.push(ptr);
			ptr += m_BlockSize;
		}

		m_TotalBlockNum += blockNum;
	}

	void* Allocator::pnew(U32 size)
	{
		if (size <= m_BlockSize) {
			// ������������Ȃ��ꍇ�͒ǉ�
			if (m_AllocatablePtr.empty()) {
				AddBlock();
			}

			auto ptr=m_AllocatablePtr.top();
			m_AllocatablePtr.pop();

			return ptr;
		}
		return nullptr;
	}

	void Allocator::pdel(void*& ptr)
	{
		if (ptr == nullptr)return;
		for (auto header : m_MemoryList)
		{
			// �͈͓��`�F�b�N
			if (header.ptr <= ptr && ptr <= (Byte*)header.ptr + header.size) {
				/// TODO:�������ʒu���u���b�N�T�C�Y�̔{�����`�F�b�N
				m_AllocatablePtr.push(ptr);
				ptr = nullptr;
				return;
			}
		}
		free(ptr);
		ptr = nullptr;
	}

	U32 Allocator::GetBlockSize() const{
		return m_BlockSize;
	}
}