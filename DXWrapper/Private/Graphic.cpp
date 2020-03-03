#include "DX12Wrapper.h"
#include "OrigamiAPI.h"

using namespace DirectX;

namespace OrigamiGraphic
{
	void DX12Wrapper::CreateTextureLoaderTable() {
		m_LoadLambdaTable[L"bmp"] = 
		m_LoadLambdaTable[L"png"] = 
		m_LoadLambdaTable[L"jpg"] = [](const String& path, TexMetadata* meta, ScratchImage& img)->HRESULT {
			return LoadFromWICFile(path.c_str(), 0, meta, img);
		};

		m_LoadLambdaTable[L"tga"] = [](const String& path, TexMetadata* meta, ScratchImage& img)->HRESULT {
			return LoadFromTGAFile(path.c_str(), meta, img);
		};

		m_LoadLambdaTable[L"dds"] = [](const String& path, TexMetadata* meta, ScratchImage& img)->HRESULT {
			return LoadFromDDSFile(path.c_str(), 0, meta, img);
		};
	}


	int DX12Wrapper::LoadGraph(const String& path)
	{
		//テクスチャのロード
		TexMetadata metadata = {};
		ScratchImage scratchImg = {};
		auto extention = path.substr(path.find_last_of('.'));

		if (m_LoadLambdaTable.find(extention) == m_LoadLambdaTable.end()) {
			return -1;
		}

		auto result = m_LoadLambdaTable[extention](path,&metadata,scratchImg);
		if (FAILED(result)) {
			return -1;
		}
		auto img = scratchImg.GetImage(0, 0, 0);//生データ抽出

		//WriteToSubresourceで転送する用のヒープ設定
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(metadata.format, metadata.width, metadata.height, metadata.arraySize, metadata.mipLevels);

		ComPtr<ID3D12Resource> texbuff = nullptr;
		result = m_Dev->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,//特に指定なし
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(texbuff.ReleaseAndGetAddressOf())
		);

		if (FAILED(result)) {
			return -1;
		}
		result = texbuff->WriteToSubresource(0,
			nullptr,//全領域へコピー
			img->pixels,//元データアドレス
			img->rowPitch,//1ラインサイズ
			img->slicePitch//全サイズ
		);
		if (FAILED(result)) {
			return -1;
		}

		m_TextureMap.push_back(texbuff);

		return m_TextureMap.size()-1;

		return 0;
	}
}