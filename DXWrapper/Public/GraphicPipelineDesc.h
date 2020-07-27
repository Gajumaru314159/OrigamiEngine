#pragma once
#include "IShader.h"

namespace og
{
	/// <summary>
	/// シェーダプログラムに使用できる変数の型
	/// </summary>
	enum class ShaderParamType
	{
		UNDEFINED,
		BOOL,
		INT,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		TEXTURE2D,
		TEXTURE3D,
		MATRIX
	};


	/// <summary>
	/// 描画に使用するトポロジーの種類
	/// </summary>
	enum class PrimitiveTopology
	{
		POINT,
		LINE,
		TRIANGLE
	};


	/// <summary>
	/// 描画時に使用する合成モード
	/// </summary>
	enum class BlendMode
	{
		MIX,
		ADD,
		SUBSTRACT,
		DARKEST,
		LIGHTEST,
		DIFF,
		MULTIPLY,
		SCREEN,
		INVERT,
		REPLACE
	};


	enum class CullMode
	{
		BACK,
		FRONT,
		NONE
	};

	/// <summary>
	/// グラフィックパイプラインの定義
	/// </summary>
	struct GraphicPipelineDesc
	{
		// シェーダID
		SPtr<IShader> vs = nullptr;
		SPtr<IShader> ps = nullptr;
		SPtr<IShader> gs = nullptr;
		SPtr<IShader> hs = nullptr;
		SPtr<IShader> ds = nullptr;

		bool useWireframe = false;
		CullMode cullMode= CullMode::BACK;
		bool useMultisample = true;
		bool useDepth = true;
		bool useStencil = true;


		// その他

		PrimitiveTopology primitiveTopologyType = PrimitiveTopology::TRIANGLE;

		// レンダ―ターゲット
		S32 numRenderTargets = 1;
		BlendMode blendMode[8];
	};



	// シェーダパラメータ情報
	struct ShaderVariableDesc
	{
		ShaderParamType type;
		S32 offset;
		S32 elementCount;
		S32 registerNum;
	};
}