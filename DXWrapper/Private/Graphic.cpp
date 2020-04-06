#include "pch.h"
#include "DX12Wrapper.h"

#include <stdexcept>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

#define OUT_OF_RANGE(container,index) (index<0||container.size()<=index)



namespace OrigamiGraphic
{
	void DX12Wrapper::CreateTextureLoaderTable()
	{
		m_LoadLambdaTable[L"bmp"] =
			m_LoadLambdaTable[L"png"] =
			m_LoadLambdaTable[L"jpg"] = [](const String& path, TexMetadata* meta, ScratchImage& img) -> HRESULT {
			return LoadFromWICFile(path.c_str(), 0, meta, img);
		};

		m_LoadLambdaTable[L"tga"] = [](const String& path, TexMetadata* meta, ScratchImage& img) -> HRESULT {
			return LoadFromTGAFile(path.c_str(), meta, img);
		};

		m_LoadLambdaTable[L"dds"] = [](const String& path, TexMetadata* meta, ScratchImage& img) -> HRESULT {
			return LoadFromDDSFile(path.c_str(), 0, meta, img);
		};
	}

	S32 DX12Wrapper::LoadGraph(const String& path)
	{
		//テクスチャのロード
		TexMetadata metadata = {};
		ScratchImage scratchImg = {};

		auto extention = path.substr(path.find_last_of('.'));

		if (m_LoadLambdaTable.find(extention) == m_LoadLambdaTable.end())
		{
			return -1;
		}

		// 読み込み
		auto result = m_LoadLambdaTable[extention](path, &metadata, scratchImg);
		if (FAILED(result))
		{
			return -1;
		}
		auto img = scratchImg.GetImage(0, 0, 0);  //生データ抽出

		//WriteToSubresourceで転送する用のヒープ設定
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			metadata.format,
			(UINT16)metadata.width,
			(UINT)metadata.height,
			(UINT16)metadata.arraySize,
			(UINT16)metadata.mipLevels);

		ComPtr<ID3D12Resource> texbuff = nullptr;
		result = m_Dev->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,  //特に指定なし
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(texbuff.ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
			return -1;
		}
		result = texbuff->WriteToSubresource(0,
											 nullptr,               //全領域へコピー
											 img->pixels,           //元データアドレス
											 (UINT)img->rowPitch,   //1ラインサイズ
											 (UINT)img->slicePitch  //全サイズ
		);
		if (FAILED(result))
		{
			return -1;
		}


		m_TextureList.push_back(texbuff);

		return (int)m_TextureList.size() - 1;
	}


	S32 DX12Wrapper::LoadShader(const String& path, ShaderType type, String& errorDest)
	{
		if (IsCompiledShader(path))
		{
		}

		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;


		static const char entryPoints[][16] =
		{
			"VSMain",
			"PSMain"
		};
		static const char targets[][16] =
		{
			"vs_5_0",
			"ps_5_0"
		};

		// シェーダのコンパイル
		auto result = D3DCompileFromFile(
			path.c_str(),                                     // ファイル名
			nullptr,                                          // シェーダーマクロ
			D3D_COMPILE_STANDARD_FILE_INCLUDE,                // シェーダ内でインクルードする場合カレントディレクトリを参照する
			entryPoints[(U32)type],                           // エントリポイント
			targets[(U32)type],                               // どのシェーダを割り当てるか
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,  // コンパイルオプション
			0,                                                // エフェクトコンパイルオプション
			&shaderBlob,
			&errorBlob);

		if (FAILED(result))
		{
			if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				errorDest = path + L" dose not exist.";
			}
			else
			{
				errorDest.resize(errorBlob->GetBufferSize());
				std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errorDest.begin());
			}
			return -1;
		}

		m_ShaderList.push_back(shaderBlob);
		return (S32)m_ShaderList.size() - 1;
	}

	S32 DX12Wrapper::DeleteShader(const S32 id)
	{
		if (OUT_OF_RANGE(m_ShaderList, id))return -1;
		if (m_ShaderList.at(id) == nullptr)return -1;

		auto count = m_ShaderList.at(id)->Release();
		if (0 <= count)m_ShaderList.at(id)->AddRef();
		return 0;
	}


	S32 DX12Wrapper::CreateGraphicPipeline(const PipelineDesc& desc)
	{
		// 頂点レイアウトの指定
		D3D12_INPUT_ELEMENT_DESC inputLayout[4] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		};
		U32 layoutSize = 1;
		{
			if (desc.useNormal)
			{
				inputLayout[layoutSize] = { "NORMAL",0,	DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };
				layoutSize++;
			}
			if (desc.useTexcoord)
			{
				inputLayout[layoutSize] = { "TEXCOORD",0,	DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };
				layoutSize++;
			}
		}



		//レンジ
		CD3DX12_DESCRIPTOR_RANGE descTblRanges[3] = {};
		descTblRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);							// 変換行列
		descTblRanges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);							// マテリアルパラメータ
		descTblRanges[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, desc.textureNameList.size(), 0);	// テクスチャ

		//ルートパラメータ
		CD3DX12_ROOT_PARAMETER rootParams[2] = {};
		rootParams[0].InitAsDescriptorTable(1, &descTblRanges[0]);  // オブジェクト毎	(変換行列)
		rootParams[1].InitAsDescriptorTable(2, &descTblRanges[1]);  // マテリアル毎		(パラメータ/テクスチャ)

		// サンプラー
		CD3DX12_STATIC_SAMPLER_DESC samplerDescs[1] = {};
		samplerDescs[0].Init(0);


		// ルートシグネチャディスクリプタ
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Init(2, rootParams, 1, samplerDescs, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);



		// バイナリデータの作成
		ComPtr<ID3DBlob> rootSigBlob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;

		auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		if (FAILED(result))
		{
			return -1;
		}

		// ルートシグネチャの作成
		ID3D12RootSignature* rootSignature;
		result = m_Dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
		if (FAILED(result))
		{
			return -1;
		}


		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
		gpipeline.pRootSignature = rootSignature;

		gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;  //中身は0xffffffff

		gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

		gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  //カリングしない

		gpipeline.DepthStencilState.DepthEnable = true;                        //深度バッファを使うぞ
		gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;  //全て書き込み
		gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;  //小さい方を採用
		gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		gpipeline.DepthStencilState.StencilEnable = false;

		gpipeline.InputLayout.pInputElementDescs = inputLayout;     //レイアウト先頭アドレス
		gpipeline.InputLayout.NumElements = layoutSize;				//レイアウト配列数

		gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;	//ストリップ時のカットなし
		gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;	//三角形で構成

		gpipeline.NumRenderTargets = desc.numRenderTargets;		//レンダ―ターゲットの数
		for (S32 i = 0; i < _countof(desc.blendMode); i++)
		{
			gpipeline.RTVFormats[i] = DXGI_FORMAT_R8G8B8A8_UNORM;	//0～1に正規化されたRGBA
		}

		gpipeline.SampleDesc.Count = 1;  //サンプリングは1ピクセルにつき１
		gpipeline.SampleDesc.Quality = 0;  //クオリティは最低


		// シェーダ設定
		if (OUT_OF_RANGE(m_ShaderList, desc.vertexShaderID))return -1;
		if (OUT_OF_RANGE(m_ShaderList, desc.pixelShaderID))return -1;

		if (m_ShaderList.at(desc.vertexShaderID) == nullptr)return -1;
		if (m_ShaderList.at(desc.pixelShaderID) == nullptr)return -1;

		gpipeline.VS = CD3DX12_SHADER_BYTECODE(m_ShaderList.at(desc.vertexShaderID).Get());
		gpipeline.PS = CD3DX12_SHADER_BYTECODE(m_ShaderList.at(desc.pixelShaderID).Get());

		m_ShaderList.at(desc.vertexShaderID)->AddRef();
		m_ShaderList.at(desc.pixelShaderID)->AddRef();



		ID3D12PipelineState* pipelineState;
		result = m_Dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState));
		if (FAILED(result))
		{
			//作成に失敗したので参照を減らす
			m_ShaderList.at(desc.vertexShaderID)->Release();
			m_ShaderList.at(desc.pixelShaderID)->Release();
			return -1;
		}

		m_PipelineList.push_back({ desc,pipelineState, rootSignature });
		return (S32)m_PipelineList.size() - 1;
	}

	S32 DX12Wrapper::DeleteGraphicPipeline(const S32 id)
	{
		if (OUT_OF_RANGE(m_PipelineList, id))return -1;
		auto& pipeline = m_PipelineList.at(id);
		if (pipeline.referenceCount != 0) return -1;
		pipeline.pipelineState.Reset();
		pipeline.rootSignature.Reset();

		// 参照しているシェーダオブジェクトへの参照を切る
		if (0 <= pipeline.desc.vertexShaderID)m_ShaderList.at(pipeline.desc.vertexShaderID)->Release();
		if (0 <= pipeline.desc.pixelShaderID)m_ShaderList.at(pipeline.desc.pixelShaderID)->Release();
		if (0 <= pipeline.desc.geometoryShaderID)m_ShaderList.at(pipeline.desc.geometoryShaderID)->Release();
		if (0 <= pipeline.desc.hullShaderID)m_ShaderList.at(pipeline.desc.hullShaderID)->Release();
		if (0 <= pipeline.desc.tessellationShaderID)m_ShaderList.at(pipeline.desc.tessellationShaderID)->Release();
		if (0 <= pipeline.desc.domainShaderID)m_ShaderList.at(pipeline.desc.domainShaderID)->Release();
		return 0;
	}



	S32 DX12Wrapper::CreateMaterial(const S32 id)
	{
		if (id < 0 || m_PipelineList.size() <= id)return -1;
		// パイプラインが削除されていたら終了
		if (m_PipelineList.at(id).pipelineState == nullptr)return -1;

		auto& pipelineSet = m_PipelineList[id];

		// シェーダパラメータのサイズ計算
		S32 shaderDataSize = 0;
		for (auto& data : pipelineSet.desc.shaderParamMap)
		{
			shaderDataSize += GetShaderDataSize(data.second.type);
		}


		// マテリアルの追加
		SPtr<Material> material = MSPtr<Material>();

		material->pipelineID = id;
		material->data.resize(shaderDataSize);

		//======================================//
		// シェーダパラメータ
		//======================================//

		// シェーダパラメータをGPUに確保
		auto result = m_Dev->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer((shaderDataSize + 0xff) & ~0xff),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(material->resource.ReleaseAndGetAddressOf())
		);
		// マップ
		result = material->resource->Map(0, nullptr, (void**)material->data.data());//マップ


		// シェーダパラメータ用ディスクリプタ
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
		descHeapDesc.NodeMask = 0;//マスクは0
		descHeapDesc.NumDescriptors = 1;//ビューは１つだけ
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//シェーダリソースビュー(および定数、UAVも)

		// ディスクリプタヒープの作成
		result = m_Dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(material->descHeap.ReleaseAndGetAddressOf()));


		//デスクリプタの先頭ハンドルを取得しておく
		auto heapHandle = material->descHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = material->resource->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = (UINT)(material->resource->GetDesc().Width);
		//定数バッファビューの作成
		m_Dev->CreateConstantBufferView(&cbvDesc, heapHandle);

		//======================================//
		// テクスチャ
		//======================================//

		S32 texNum = pipelineSet.desc.textureNameList.size();

		// マテリアル用ディスクリプタヒープ
		ID3D12DescriptorHeap* materialDescHeap = nullptr;
		D3D12_DESCRIPTOR_HEAP_DESC materialDescHeapDesc = {};
		materialDescHeapDesc.NumDescriptors = 1 + texNum;//定数1つ+テクスチャ)
		materialDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		materialDescHeapDesc.NodeMask = 0;

		materialDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別
		result = m_Dev->CreateDescriptorHeap(&materialDescHeapDesc, IID_PPV_ARGS(&materialDescHeap));//生成


		// 通常テクスチャビュー作成
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//後述
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
		srvDesc.Texture2D.MipLevels = 1;//ミップマップは使用しないので1

		auto matDescHeapH = materialDescHeap->GetCPUDescriptorHandleForHeapStart();
		auto incSize = m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		// パラメータのビューを生成
		m_Dev->CreateConstantBufferView(&cbvDesc, matDescHeapH);
		matDescHeapH.ptr += incSize;

		//テクスチャのビューを生成
		for (int i = 0; i < texNum; i++)
		{
			srvDesc.Format = m_TextureList[m_whiteTexID]->GetDesc().Format;
			m_Dev->CreateShaderResourceView(
				m_TextureList[m_whiteTexID].Get(),
				&srvDesc,
				matDescHeapH
			);
			matDescHeapH.ptr += incSize;
		}


		S32 materialID = m_MaterialList.size();
		m_MaterialList.push_back(MSPtr<Material>());
		return materialID;
	}

	S32 DX12Wrapper::DeleteMaterial(const S32 id)
	{
		if (OUT_OF_RANGE(m_MaterialList, id))return -1;
		auto& material = m_MaterialList.at(id);
		if (material.use_count() != 0 || 1 < material.use_count())return -1;

		material.reset();
		m_PipelineList.at(material->pipelineID).referenceCount--;
	}



	S32 DX12Wrapper::SetMaterial(const S32 id)
	{
		if (OUT_OF_RANGE(m_MaterialList, id))return -1;
		auto& material = *m_MaterialList[id];
		// パイプラインの設定
		S32 pipelineID = material.pipelineID;
		m_CmdList->SetPipelineState(m_PipelineList[pipelineID].pipelineState.Get());
		m_CmdList->SetComputeRootSignature(m_PipelineList[pipelineID].rootSignature.Get());

		// マテリアルパラメータの設定

		// ディスクリプタの指定
		ID3D12DescriptorHeap* sceneheaps[] = { material.descHeap.Get() };
		m_CmdList->SetDescriptorHeaps(1, sceneheaps);
		// ルートパラメータとディスクリプタの関連づけ
		m_CmdList->SetGraphicsRootDescriptorTable(0, material.descHeap->GetGPUDescriptorHandleForHeapStart());


		// テクスチャの設定
	}


	S32 DX12Wrapper::SetMaterialFloatParam(const String& name, const F32 value)
	{
		if (OUT_OF_RANGE(m_MaterialList, m_CurrentMaterialID))return -1;

		S32 pipelineID = m_MaterialList[m_CurrentMaterialID]->pipelineID;

		if (OUT_OF_RANGE(m_PipelineList, pipelineID))return -1;

		// シェーダパラメータがない場合
		if (m_PipelineList[pipelineID].desc.shaderParamMap.count(name))return -1;

		S32 offset = m_PipelineList[pipelineID].desc.shaderParamMap[name].index;


		auto ptr = m_MaterialList[m_CurrentMaterialID]->data.data();
		*reinterpret_cast<F32*>(ptr + offset) = value;

		return 0;
	}




	S32 DX12Wrapper::CreateTexture(S32 width, S32 height, TextureFormat format)
	{
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(ConvertTextureFormat(format), width, height);
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

		ID3D12Resource* textureBuff = nullptr;
		auto result = m_Dev->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(&textureBuff)
		);
		if (FAILED(result))
		{
			return -1;
		}

		std::vector<unsigned char> data(width * height * GetTextureFormatSize(format));
		std::fill(data.begin(), data.end(), 0xff);

		result = textureBuff->WriteToSubresource(0, nullptr, data.data(), width * height, data.size());
		if (FAILED(result))
		{
			return -1;
		}

		m_TextureList.push_back(textureBuff);
		return m_TextureList.size() - 1;
	}


	// ここからプライベート関数

	bool DX12Wrapper::IsCompiledShader(const String& path)
	{
		std::FILE* fp;
		unsigned int id = -1;

		_wfopen_s(&fp, path.c_str(), L"rb");
		if (fp == NULL)
		{
			return false;
		}

		std::fread(&id, sizeof(id), 1, fp);  // 最初の４バイトがファイル識別子っぽい

		std::fclose(fp);

		return id == 0x43425844;
	}

	S32 DX12Wrapper::GetShaderDataSize(ShaderParamType type)
	{
		switch (type)
		{
		case OrigamiGraphic::ShaderParamType::FLOAT4:return 4 * 4;
		}
		return 0;
	}

	S32 DX12Wrapper::GetTextureFormatSize(const TextureFormat format)const
	{
		switch (format)
		{
		case TextureFormat::RGBA32:return 16;
		case TextureFormat::RGBA16:return 8;
		case TextureFormat::RGBA8:return 4;
		case TextureFormat::RG8:return 2;
		case TextureFormat::R32:return 4;
		case TextureFormat::R16:return 2;
		case TextureFormat::R8:return 1;
		case TextureFormat::Depth:return 4;
		case TextureFormat::RGB565:return 2;
		case TextureFormat::RGBA5551:return 2;
		}
	}
	DXGI_FORMAT DX12Wrapper::ConvertTextureFormat(const TextureFormat format)const
	{
		switch (format)
		{
		case TextureFormat::RGBA32:return DXGI_FORMAT_R32G32B32A32_FLOAT;//
		case TextureFormat::RGBA16:return DXGI_FORMAT_R16G16B16A16_UNORM;
		case TextureFormat::RGBA8:return DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::RG8:return DXGI_FORMAT_R8G8_SNORM;
		case TextureFormat::R32:return DXGI_FORMAT_R32_FLOAT;//
		case TextureFormat::R16:return DXGI_FORMAT_R16_UNORM;
		case TextureFormat::R8:return DXGI_FORMAT_R8_UNORM;
		case TextureFormat::Depth:return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case TextureFormat::RGB565:return DXGI_FORMAT_B5G6R5_UNORM;
		case TextureFormat::RGBA5551:return DXGI_FORMAT_B5G5R5A1_UNORM;
		}
	}


}  // namespace OrigamiGraphic