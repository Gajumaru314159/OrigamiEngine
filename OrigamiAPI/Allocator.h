/**
* @file Allocator.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine
{
	/**
	* @brief プールアロケータ
	* @details メモリをあらかじめ確保しておき、定量ずつ切り出して割り当てていく。メモリが足りない場合はメモリ空間を倍にする。
	*/
	class Allocator
	{
	public:
		/**
		* @brief コンストラクタ。
		* @param blockSize 割り当てることのできるブロックの最大サイズ。最小値は4バイト。初期値は64バイト。
		* @param 割り当てることのできブロックの数。初期値は1024。
		*/
		Allocator(U32 blockSize=64,U32 blockNum=1024);
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&)=delete;

		virtual ~Allocator();

		/**
		* @brief 指定したサイズのメモリを追加で確保する。
		* @param blockNum 確保するブロックの数。0の場合現在確保されているブロックと同じ数確保する。
		*/
		void AddBlock(U32 blockNum=1);


		/**
		* @brief メモリの割り当て要求。
		* @details 指定した型サイズがブロックサイズ以下なら事前に確保したメモリから割り当てられ、以上ならnullを返す。
		*/
		void* pnew(U32 size);

		/**
		* @brief 確保したメモリを返却する。
		* @details 返却するとメモリの所有権がなくなりメモリの値は未定義となる。また管轄外のポインタを渡した場合も未定義となる。
		* @param 返却するメモリのポインタ
		*/
		void pdel(void*& ptr);



		U32 GetBlockSize()const;

	private:

		/**
		* @brief 確保したメモリのポインタとサイズを管理
		*/
		struct Header
		{
			void* ptr=nullptr;
			U32 size=0;
		};



		// 割り当てることのできるブロックの最大サイズ。
		U32 m_BlockSize;
		// 割り当てることのできるブロックの数。
		U32	m_TotalBlockNum;

		// 独自に割り当てるメモリ空間のポインタ。
		ArrayList<Header> m_MemoryList;


		// 割り当て可能なメモリブロックのスタック。
		Stack<void*> m_AllocatablePtr;
	};
}