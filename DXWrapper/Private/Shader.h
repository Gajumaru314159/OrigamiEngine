﻿#pragma once

#include "IShader.h"
#include "GraphicPipelineDesc.h"

#include <d3d12.h>

#include "IGraphicWrapper.h"
#include "DXHelper.h"


namespace og
{
	class Shader :public IShader
	{
	private:
		ComPtr<ID3DBlob> m_shaderBolb;

		ArrayList<D3D12_INPUT_ELEMENT_DESC> m_inputLayoutDesc;
		ArrayList<D3D12_INPUT_ELEMENT_DESC> m_textureDesc;

	public:

		/// <summary>
		/// シェーダーコードからシェーダーオブジェクトを生成
		/// </summary>
		/// <remarks>
		/// コンパイルに失敗した場合はエラー出力先文字列にエラーログが格納される。
		/// </remarks>
		/// <param name="src">シェーダー文字列</param>
		/// <param name="type">シェーダーステージ</param>
		/// <param name="errorDest">エラー出力先文字列</param>
		Shader(const String& src, const ShaderType type, String& errorDest);

		Shader(ComPtr<ID3DBlob>& bolb);


		const ComPtr<ID3DBlob>& GetShaderBolb() { return m_shaderBolb; }


		/// <summary>
		/// シェーダーオブジェクトが有効な状態かどうか
		/// </summary>
		/// <remarks>
		/// シェーダーの生成を行った場合はこの関数を用いて生成に成功したかを判定できる。
		/// </remarks>
		inline bool IsValid()const { return m_shaderBolb; };

	public:
		/// <summary>
		/// シェーダーで使用される変数の型ごとの使用メモリサイズを調べる
		/// </summary>
		/// <param name="type">シェーダー変数の型</param>
		/// <returns>使用メモリサイズ</returns>
		static S32 GetShaderDataSize(const ShaderParamType type);

		/// <summary>
		/// 対称のファイルがコンパイル済みシェーダーオブジェクトか判定する
		/// </summary>
		/// <param name="path">ファイルパス</param>
		/// <returns>ファイルがコンパイル済みであればtrueを返す</returns>
		static bool IsCompiledShader(const String& path);

		/// <summary>
		/// ファイルからシェーダーオブジェクトを生成する
		/// </summary>
		/// <param name="path">ファイルパス</param>
		/// <param name="type">シェーダーステージ</param>
		/// <param name="errorDest">エラー出力先文字列</param>
		/// <returns>シェーダーオブジェクトのスマートポインタ</returns>
		static UPtr<Shader> LoadFromFile(const String& path, const ShaderType type, String& errorDest);
	};
}