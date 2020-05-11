#pragma once
#include <wrl.h>

#include <d3d12.h>

#include "InnerGraphicPipelineDesc.h"


namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

struct ID3D12ShaderReflection;
namespace og
{
	/// <summary>
	/// 描画に使用する情報をひとまとめにする
	/// </summary>
	class GraphicPipeline
	{
	public:
		static const S32 MAX_CONSTANT_BUFFER = 16;
	private:
		// メインリソース
		ComPtr<ID3D12PipelineState> m_PipelineState;
		ComPtr<ID3D12RootSignature> m_RootSignature;

		// シェーダ参照
		ComPtr<ID3DBlob> m_VS;
		ComPtr<ID3DBlob> m_PS;
		ComPtr<ID3DBlob> m_GS;
		ComPtr<ID3DBlob> m_HS;
		ComPtr<ID3DBlob> m_DS;



		// 頂点レイアウトの定義
		ArrayList<String> m_InputLayoutNames;
		ArrayList<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

		HashMap<String, ShaderVariableDesc> m_Data;
		U32 m_ConstantBufferSizes[MAX_CONSTANT_BUFFER];
		S32 m_TextureNum;

	public:
		GraphicPipeline(ComPtr<ID3D12Device>& device, const InnerGraphicPipelineDesc& desc);

		/// <summary>
		/// コマンドリストにこのグラフィックパイプラインを設定する
		/// </summary>
		/// <param name="commandList">グラフィックコマンドリスト</param>
		/// <returns></returns>
		S32 SetGraphicPipeline(ComPtr<ID3D12GraphicsCommandList>& commandList)const;

		/// <summary>
		/// 指定したレジスタの定数バッファのサイズを取得
		/// </summary>
		/// <param name="index">レジスタ番号</param>
		/// <returns></returns>
		S32 GetConstantBufferSize(const U32 index)const;

		/// <summary>
		/// 使用するテクスチャの枚数を取得
		/// </summary>
		///  <param name="index">レジスタ番号</param>
		/// <returns>枚数</returns>
		S32 GetTextureNum()const;

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
		inline bool IsValid()const { return m_PipelineState != nullptr; }

	private:
		S32 ReflectShader(const ComPtr<ID3DBlob>& vsBolb);
		S32 ReflectInputLayout(const ComPtr<ID3DBlob>& vsBolb);
		S32 ReflectConstantBuffer(const ComPtr<ID3D12ShaderReflection>& reflection);
		S32 ReflectBoundingResource(const ComPtr<ID3D12ShaderReflection>& reflection);
		S32 ReflectOutputLayout(const ComPtr<ID3DBlob>& vsBolb);
	};
}