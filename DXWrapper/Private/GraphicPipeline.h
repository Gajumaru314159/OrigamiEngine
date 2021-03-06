﻿#pragma once

#include <d3d12.h>
#include "IGraphicPipeline.h"
#include "GraphicPipelineDesc.h"

#include "DXHelper.h"

struct ID3D12ShaderReflection;
namespace og
{
	/// <summary>
	/// 描画に使用する情報をひとまとめにする
	/// </summary>
	class GraphicPipeline :public IGraphicPipeline
	{
	public:
		static const S32 MAX_REGISTER = 32;
	private:
		// メインリソース
		ComPtr<ID3D12PipelineState> m_pipelineState;
		ComPtr<ID3D12RootSignature> m_rootSignature;

		// シェーダ参照
		SPtr<IShader> m_vs;
		SPtr<IShader> m_ps;
		SPtr<IShader> m_gs;
		SPtr<IShader> m_hs;
		SPtr<IShader> m_ds;



		// 頂点レイアウトの定義
		ArrayList<String> m_inputLayoutNames;
		ArrayList<D3D12_INPUT_ELEMENT_DESC> m_inputLayout;

		// 変数定義マップ
		HashMap<String, ShaderVariableDesc> m_varMap;

		// 定数バッファのレジスタごとのサイズ
		U32 m_cBufDataSizes[MAX_REGISTER];
		// テクスチャのレジスタごとの枚数
		U32 m_texNums[MAX_REGISTER];


		S32 m_cBufIndices[MAX_REGISTER];
		S32 m_texIndices[MAX_REGISTER];

		// レンダーターゲットの枚数
		S32 m_targetNum;

	public:
		GraphicPipeline(const GraphicPipelineDesc& desc);


		/// <summary>
		/// コマンドリストにこのグラフィックパイプラインを設定する
		/// </summary>
		/// <param name="commandList">グラフィックコマンドリスト</param>
		/// <returns>　０：成功\n－１：失敗</returns>
		S32 SetGraphicPipeline(ComPtr<ID3D12GraphicsCommandList>& commandList)const;

		/// <summary>
		/// 指定したレジスタの定数バッファのサイズを取得
		/// </summary>
		/// <param name="resister">レジスタ番号</param>
		/// <returns>定数バッファのサイズ</returns>
		S32 GetConstantBufferSize(const U32 resister)const;

		/// <summary>
		/// 指定したレジスタのテクスチャの枚数を取得
		/// </summary>
		///  <param name="resister">レジスタ番号</param>
		/// <returns>枚数</returns>
		S32 GetTextureNum(const U32 resister)const;

		/// <summary>
		/// 指定した定数バッファのレジスタがディスクリプタヒープの何番目に割り当てられているかを取得
		/// </summary>
		/// <param name="resister"></param>
		/// <returns>－１以外：インデックス\n　　－１：指定したレジスタがマテリアルに含まれていない</returns>
		S32 GetConstantBufferIndex(const U32 resister)const;

		/// <summary>
		/// 指定したテクスチャのレジスタがディスクリプタヒープの何番目に割り当てられているかを取得
		/// </summary>
		/// <param name="resister"></param>
		/// <returns>－１以外：インデックス\n　　－１：指定したレジスタがマテリアルに含まれていない</returns>
		S32 GetTextureIndex(const U32 resister)const;

		/// <summary>
		/// シェーダー変数の情報を変数名から取得する
		/// </summary>
		/// <param name="name">変数名</param>
		/// <returns>変数が存在する場合は変数情報を返す。存在しない場合は変数情報のレジスタ番号が-1となる。</returns>
		ShaderVariableDesc GetVariableData(const String& name)const;

		/// <summary>
		/// シェーダーに含まれる変数の一覧を取得する
		/// </summary>
		/// <param name="dest">変数データの出力先のリスト</param>
		/// <returns>　０：取得成功\n－１：取得失敗</returns>
		const HashMap<String, ShaderVariableDesc>& GetShaderParamList()const;


		/// <summary>
		/// インスタンスの生成に成功しているか
		/// </summary>
		/// <returns></returns>
		inline bool IsValid()const { return m_pipelineState != nullptr; }

	private:
		S32 ReflectShader(const ComPtr<ID3DBlob>& vsInstance);
		S32 ReflectInputLayout(const ComPtr<ID3DBlob>& vsInstance);
		S32 ReflectConstantBuffer(const ComPtr<ID3D12ShaderReflection>& reflection);
		S32 ReflectBoundingResource(const ComPtr<ID3D12ShaderReflection>& reflection);
		S32 ReflectOutputLayout(const ComPtr<ID3DBlob>& vsInstance);
	};
}