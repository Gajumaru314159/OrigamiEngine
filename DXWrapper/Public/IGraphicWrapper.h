#pragma once

#include <memory>


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
	class IGraphicWrapper
	{
	public:
		/// <summary>
		/// ライブラリ内で生成されたインスタンスをライブラリ内で適切に削除する。
		/// </summary>
		virtual void Delete() { delete this; };

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
		virtual S32 SwapScreen() = 0;


		//===================================================================================//

		/// <summary>
		/// 書き込み可能なテクスチャを生成
		/// </summary>
		/// <remarks>関数が成功するとライブラリから割り当てられたIDを返す。</remarks>
		/// <param name="width">横幅</param>
		/// <param name="height">高さ</param>
		/// <param name="format">生成する画像のピクセルフォーマット</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 CreateTexture(const S32 width, const S32 height, const TextureFormat format) = 0;
		/// <summary>
		/// 画像ファイルの読み込み
		/// </summary>
		/// <remarks>
		/// グラフィックデータをGPU上に確保する。関数が成功するとライブラリから割り当てられたIDを返す。
		/// </remarks>
		/// <param name="path">ファイルパス</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 LoadGraph(const String& path) = 0;

		//===================================================================================//

		/// <summary>
		/// シェーダの読み込み
		/// </summary>
		/// <remarks>読み込まれたシェーダがコンパイル済みであればそのまま読み込み、そうでなければHLSL5.0でコンパイルする。関数が成功するとライブラリから割り当てられたIDを返す。コンパイルに失敗した場合はエラー内容を文字列としてerrorDestに出力する。</remarks>
		/// <param name="path">ファイルパス</param>
		/// <param name="type">シェーダの種類</param>
		/// <param name="errorDest">エラーログ</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 LoadShader(const String& path, ShaderType type, String& errorDest) = 0;

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
		virtual S32 CreateShader(const String& src, ShaderType type, String& errorDest) = 0;

		/// <summary>
		/// シェーダオブジェクトの削除
		/// </summary>
		/// <remarks>
		/// 指定したIDのシェーダをメモリから削除する。シェーダを使用しているパイプラインが存在する場合は削除に失敗する。
		/// </remarks>
		/// <param name="id">シェーダID</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 DeleteShader(const S32 id) = 0;

		//===================================================================================//

		/// <summary>
		/// グラフィックパイプラインの作成
		/// </summary>
		/// <remarks>
		/// 各シェーダを組み合わせ、グラフィックパイプラインを構築する。関数が成功するとライブラリから割り当てられたIDを返す。シェーダIDに-1を指定すると、標準のシェーダが適用される。
		/// </remarks>
		/// <param name="desc">グラフィックパイプラインの定義データ</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 CreateGraphicPipeline(const GraphicPipelineDesc& desc) = 0;

		/// <summary>
		/// グラフィックパイプラインの削除
		/// </summary>
		/// <remarks>
		/// 指定したIDのグラフィックパイプラインをメモリから削除する。パイプラインを使用しているマテリアルが存在する場合は削除に失敗する。
		/// </remarks>
		/// <param name="id">グラフィックパイプラインID</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 DeleteGraphicPipeline(const S32 id) = 0;

		/// <summary>
		/// 描画パイプラインのセット
		/// </summary>
		/// <param name="id">使用するグラフィックパイプラインのID</param>
		/// <returns>　－１　　　:　エラー\n－１以外　:　ID</returns>
		virtual S32 SetGraphicPipeline(const S32 id) = 0;

		/// <summary>
		/// グラフィックパイプラインに定義されているシェーダー変数のリストを取得
		/// </summary>
		/// <param name="graphicPipelineID">グラフィックパイプラインID</param>
		/// <param name="dest">リストの出力先</param>
		/// <returns>－１　:　エラー\n　０　:　成功</returns>
		virtual const HashMap<String, ShaderVariableDesc>& GetShaderParamList(const S32 graphicPipelineID) = 0;

		//===================================================================================//

		virtual S32 CreateMaterial(const S32 id, const S32 mask) = 0;

		virtual S32 DeleteMaterial(const S32 id) = 0;

		virtual S32 SetMaterial(const S32 id) = 0;

		virtual S32 LockMaterial(const S32 materialID) = 0;

		//virtual S32 SetShaderFloatParam(const S32 id, const String& name, const float value) = 0;
		virtual S32 SetShaderFloat4Param(const S32 id, const String& name, const Vector4& value) = 0;
		//virtual S32 SetShaderMatrixParam(const S32 id, const String& name, const float* value) = 0;
		//virtual S32 SetShaderTexture2DParam(const S32 id, const String& name, const S32 value) = 0;

		//===================================================================================//

		virtual S32 CreateShape(const U32 stribeSize, const U32 dataSize, const Byte* data, const U32 indexNum = 0, const U32* indicis = nullptr) = 0;

		//virtual S32 SetVertexData(const S32 id, const Byte*) = 0;


		//virtual S32 CreateIndexData(const S32* indces, const S32 indexNum) = 0;




		//===================================================================================//

		virtual S32 DrawShape(const S32 id) = 0;


		//===================================================================================//

		virtual ~IGraphicWrapper() {};
	};
}

namespace std
{
	template <>
	struct default_delete<og::IGraphicWrapper>
	{
		void operator()(og::IGraphicWrapper* p) const
		{
			p->Delete();
		}
	};
}