#pragma once

#include <memory>

#include "IDeletable.h"
#include "ITexture.h"
#include "IRenderTexture.h"
#include "IMaterial.h"
#include "IShader.h"
#include "IShape.h"
#include "IGraphicPipeline.h"
#include "GraphicPipelineDesc.h"

namespace og
{
	/// <summary>
	/// シェーダの種類
	/// </summary>
	enum class ShaderType
	{
		VERTEX,
		PIXEL
	};

	/// <summary>
	/// テクスチャフォーマット
	/// </summary>
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


	/// <summary>
	/// DirectXやOpenGLのようなグラフィックAPIを共通の関数を通して扱えるようにするための抽象クラス
	/// </summary>
	class IGraphicWrapper :public IDeletable
	{
	public:
		/// <summary>
		/// グラフィックライブラリの初期化
		/// </summary>
		/// <remarks>
		/// ライブラsリを使用するには、まずこの関数を呼び出す必要があります。この関数を使ってエラーが返ってきた場合は直ちにアプリを終了すること。
		/// </remarks>
		/// <returns>　０：成功<br/>－１：エラー</returns>
		virtual S32 Init() = 0;

		/// <summary>
		/// フリップ関数。裏画面を表画面に反映する。
		/// </summary>
		/// <returns>　０：成功\n－１：エラー</returns>
		virtual S32 SwapScreen(SPtr<IRenderTexture>& renderTarget) = 0;


		//===================================================================================//

		/// <summary>
		/// 書き込み可能なテクスチャを生成
		/// </summary>
		/// <remarks>関数が成功するとライブラリから割り当てられたIDを返す。</remarks>
		/// <param name="width">横幅</param>
		/// <param name="height">高さ</param>
		/// <param name="format">生成する画像のピクセルフォーマット</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual SPtr<IRenderTexture> CreateRenderTexture(const S32 width, const S32 height, const TextureFormat format) = 0;
		/// <summary>
		/// 画像ファイルの読み込み
		/// </summary>
		/// <remarks>
		/// グラフィックデータをGPU上に確保する。関数が成功するとライブラリから割り当てられたIDを返す。
		/// </remarks>
		/// <param name="path">ファイルパス</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual SPtr<ITexture> LoadTexture(const Path& path, const bool async = false) = 0;

		//===================================================================================//

		/// <summary>
		/// シェーダの読み込み
		/// </summary>
		/// <remarks>読み込まれたシェーダがコンパイル済みであればそのまま読み込み、そうでなければHLSL5.0でコンパイルする。関数が成功するとライブラリから割り当てられたIDを返す。コンパイルに失敗した場合はエラー内容を文字列としてerrorDestに出力する。</remarks>
		/// <param name="path">ファイルパス</param>
		/// <param name="type">シェーダの種類</param>
		/// <param name="errorDest">エラーログ</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual SPtr<IShader> LoadShader(const String& path, ShaderType type, String& errorDest) = 0;

		/// <summary>
		/// 文字列からシェーダを作成
		/// </summary>
		/// <remarks>
		/// 入力された文字列をHLSL5.0でコンパイルする。関数が成功するとライブラリから割り当てられたIDを返す。コンパイルに失敗した場合はエラー内容を文字列としてerrorDestに出力する。
		/// </remarks>
		/// <param name="src">ファイルパス</param>
		/// <param name="type">シェーダの種類</param>
		/// <param name="errorDest">エラーログ</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual SPtr<IShader> CreateShader(const String& src, ShaderType type, String& errorDest) = 0;

		//===================================================================================//

		/// <summary>
		/// グラフィックパイプラインの作成
		/// </summary>
		/// <remarks>
		/// 各シェーダを組み合わせ、グラフィックパイプラインを構築する。関数が成功するとライブラリから割り当てられたIDを返す。シェーダIDに-1を指定すると、標準のシェーダが適用される。
		/// </remarks>
		/// <param name="desc">グラフィックパイプラインの定義データ</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual SPtr<IGraphicPipeline> CreateGraphicPipeline(const GraphicPipelineDesc& desc) = 0;

		//===================================================================================//

		virtual SPtr<IMaterial> CreateMaterial(const SPtr<IGraphicPipeline>& pipeline, const S32 mask = -1) = 0;

		//===================================================================================//

		virtual SPtr<IShape> CreateShape(const U32 stribeSize) = 0;

		//virtual S32 DrawShape(SPtr<IShape> shape) = 0;


		//===================================================================================//



		//===================================================================================//

		virtual ~IGraphicWrapper() {};
	};
}