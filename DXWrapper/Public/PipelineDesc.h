/**
* @file
*/

#include "../../Common/Prerequisites.h"


#pragma once

namespace OrigamiGraphic
{
	enum class PrimitiveTopology
	{
		Triangles
	};

	enum class ShaderParamType
	{
		FLOAT4
	};

	struct ShaderParamDesc
	{
		ShaderParamType type;
		S32 index;
	};

	struct PipelineDesc
	{
		U32 vertexShaderID = -1;
		U32 pixelShaderID = -1;
		U32 geometoryShaderID = -1;
		U32 hullShaderID = -1;
		U32 tessellationShaderID = -1;
		U32 domainShaderID = -1;


		// 頂点レイアウト
		//bool usePosition;
		bool useNormal = false;
		bool useTexcoord = false;


		// レジスタ定義
		ArrayList<String> textureNameList;
		HashMap<String, ShaderParamDesc> shaderParamMap;



		// その他
		bool alphaToCoverageEnable = false;
		bool multisampleEnable = false;
		S32 CullingMode = false;
		bool wireframeFlag = false;
		bool useDepth = false;

		PrimitiveTopology primitiveTopologyType = PrimitiveTopology::Triangles;

		// レンダ―ターゲット
		U32 numRenderTargets;
		S32 blendMode[8];
	};
}