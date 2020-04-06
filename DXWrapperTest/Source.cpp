#include <iostream>
#include "DXWrapper.h"

using namespace std;

int main()
{
	auto ptr = CreateWrapper(OrigamiGraphic::DirectXVersion::DX12);
	if (ptr == nullptr)
	{
		cout << "ƒ‰ƒbƒp[‚Ìì¬‚ÉŽ¸”s" << endl;
		return 0;
	}

	if (ptr->Init())
	{
		cout << "‰Šú‰»Ž¸”s" << endl;
		ptr->Delete();
		return 0;
	}

	while (ptr->SwapScreen() == 0)
	{

	}
	return 0;
}