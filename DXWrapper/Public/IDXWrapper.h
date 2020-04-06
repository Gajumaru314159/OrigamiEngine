#pragma once
#include "../../Common/Prerequisites.h"
#include "PipelineDesc.h"

namespace OrigamiGraphic
{
	enum class DirectXVersion
	{
		DX12
	};

	enum class ShaderType
	{
		VERTEX,
		PIXEL
	};

	enum class TextureFormat
	{
		// RGBA
		RGBA32,
		RGBA16,
		RGBA8,
		// RG(Normal)
		RG8,
		// R
		R32,
		R16,
		R8,
		// D24S8
		Depth,
		// Other
		RGB565,
		RGBA5551
	};


	class IDXWrapper
	{
	public:
		virtual void Delete() { delete this; };

		/*
			* @brief グラフィックライブラリの初期化
			* @details ライブラリを使用するには、まずこの関数を呼び出す必要があります。\nこの関数を使ってエラーが返ってきた場合は直ちにアプリを終了すること。
			* @return 　０：成功\n－１：エラー
			*/
		virtual S32 Init() = 0;

		/**
			* @brief フリップ関数。裏画面を表画面に反映する
			* @return 　０：成功\n－１：エラー
			*/
		virtual S32 SwapScreen() = 0;

		/**
			* @brief 画像ファイルの読み込み
			* @details グラフィックデータをGPU上に確保する。関数が成功するとライブラリから割り当てられたIDを返す。
			* @param path ファイルパス
			* @return 　－１　　　:　エラー\n－１以外　:　ID
			*/
		virtual S32 LoadGraph(const String& path) = 0;




		/**
			* @brief シェーダの読み込み
			* @details 読み込まれたシェーダがコンパイル済みであればそのまま読み込み、そうでなければHLSL5.0でコンパイルする。関数が成功するとライブラリから割り当てられたIDを返す。コンパイルに失敗した場合はエラー内容を文字列としてerrorDestに出力する。
			* @param path ファイルパス
			* @param type シェーダの種類
			* @param errorDest エラーログ
			* @return 　－１　　　:　エラー\n－１以外　:　ID
			*/
		virtual S32 LoadShader(const String& path, ShaderType type, String& errorDest) = 0;
		/**
			* @brief シェーダオブジェクトの削除
			* @details 指定したIDのシェーダをメモリから削除する。シェーダを使用しているパイプラインが存在する場合は削除に失敗する。
			* @param id シェーダID
			* @return 　－１　　　:　エラー\n－１以外　:　ID
			*/
		virtual S32 DeleteShader(const S32 id) = 0;

		/**
			* @brief グラフィックパイプラインの作成
			* @details 各シェーダを組み合わせ、グラフィックパイプラインを構築する。関数が成功するとライブラリから割り当てられたIDを返す。シェーダIDに-1を指定すると、標準のシェーダが適用される。
			* @param desc グラフィックパイプラインの定義データ
			* @return 　－１　　　:　エラー\n－１以外　:　ID
			*/
		virtual S32 CreateGraphicPipeline(const PipelineDesc& desc) = 0;
		/**
			* @brief グラフィックパイプラインの削除
			* @details 指定したIDのグラフィックパイプラインをメモリから削除する。パイプラインを使用しているマテリアルが存在する場合は削除に失敗する。
			* @param id graphicパイプラインID
			* @return 　－１　　　:　エラー\n－１以外　:　ID
			*/
		virtual S32 DeleteGraphicPipeline(const S32 id) = 0;




		virtual S32 CreateMaterial(const S32 id) = 0;

		virtual S32 DeleteMaterial(const S32 id) = 0;

		virtual S32 SetMaterial(const S32 id) = 0;

		virtual S32 SetMaterialFloatParam(const String& name, const F32 value) = 0;


		virtual S32 CreateTexture(S32 width, S32 height, TextureFormat format) = 0;




		/**
			* @brief 矩形の描画
			* @param x
			* @param y
			* @param w 横幅
			* @param h 高さ
			* @param color 描画色
			*/
			//virtual void DrawRect(const F32 x, const F32 y, const F32 w, const F32 h, const FColor& color) = 0;


			//virtual void DrawIndexedMesh(const S32 id, const int* indices) = 0;
			//virtual void Set
	};
}  // namespace OrigamiGraphic

namespace std
{
	template <>
	struct default_delete<OrigamiGraphic::IDXWrapper>
	{
		void operator()(OrigamiGraphic::IDXWrapper* p) const
		{
			p->Delete();
		}
	};
};  // namespace std