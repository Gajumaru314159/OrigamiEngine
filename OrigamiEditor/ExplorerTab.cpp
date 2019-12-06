#include "ExplorerTab.h"

#include <DxLib.h>

#include "Input.h"
#include "WindowManager.h"
#include "AssetManager.h"
#include "DirectoryAsset.h"


namespace OrigamiEngine {

	ExplorerTab::ExplorerTab(int windowTex) :
		m_FontHandle(0)
	{
		m_TabName = L"Explorer";
		m_HierarchyWidth = 150;

		m_LeftArrowTex = DerivationGraph(0, 0, 22, 16, windowTex);
		m_RightArrowTex = DerivationGraph(32, 0, 22, 16, windowTex);

		m_DirectoryTex = DerivationGraph(288, 0, 16, 16, windowTex);
	}

	void ExplorerTab::OnGUI()
	{
		PlaceButton();
		PlaceButton();
		PlaceButton();
	}


	U32 ExplorerTab::DrawHierarchy(const int x, const int y, const int width, const int height)
	{
		RECT pre;
		GetDrawArea(&pre);
		SetDrawArea(x, y, x + width, y + height);

		int drawX = x + 5;
		int drawY = y + 5;

		DirectoryAsset & root = AssetManager::GetRootDirectory();
		for (const auto& child : root.GetChildren())
		{
			DrawGraph(drawX,drawY,m_DirectoryTex,TRUE);
			DrawString(drawX+18, drawY+2, child->GetName().c_str(), GetColor(255, 255, 255));

			if (typeid(*child) == typeid(DirectoryAsset))
			{
				drawY += 10;
			}
			drawY += 18;
		}


		SetDrawArea(pre.left, pre.top, pre.right, pre.bottom);
		return 0;
	}

	void ExplorerTab::DrawAssets(const int x, const int y, const int width, const int height)
	{

	}
}