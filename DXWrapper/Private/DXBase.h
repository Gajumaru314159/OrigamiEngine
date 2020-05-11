/**
* @file DXBase.h
*/

#pragma once

#include <d3d12.h>

namespace OrigamiGraphic
{
	/**
	* @brief インスタンスの生成に必要なID3D12Deviceを保持するための基底クラス
	*/
	class DXBase :Singleton<DXBase>
	{
		friend class Singleton<DXBase>;
	private:
		UPtr<ID3D12Device> m_Dev;

	public:
		
	};
}