/**
* @file Material.h
*/

#pragma once

#include "../../Common/Prerequisites.h"

namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace OrigamiGraphic
{
	struct Material
	{
	public:
		ArrayList<Byte> data;

		S32 pipelineID;
		ComPtr<ID3D12Resource> resource;
		HashMap < String, ComPtr<ID3D12Resource>> resourceMap;
		ComPtr<ID3D12DescriptorHeap> descHeap;
	};
}