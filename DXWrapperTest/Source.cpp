#include <iostream>
#include "DXWrapper.h"

using namespace std;

int main()
{
	auto ptr = CreateWrapper(OrigamiGraphic::DirectXVersion::DX12);
	if (ptr == nullptr)
	{
		cout << "ラッパーの作成に失敗" << endl;
		return 0;
	}

	if (ptr->Init())
	{
		cout << "初期化失敗" << endl;
		ptr->Delete();
		return 0;
	}

	while (ptr->SwapScreen() == 0)
	{

	}
	return 0;
}