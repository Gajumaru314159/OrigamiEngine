#include <iostream>
#include "DXWrapper.h"

using namespace std;

int main()
{
	auto ptr = CreateWrapper(OrigamiGraphic::DirectXVersion::DX12);
	if (ptr == nullptr)
	{
		cout << "���b�p�[�̍쐬�Ɏ��s" << endl;
		return 0;
	}

	if (ptr->Init())
	{
		cout << "���������s" << endl;
		ptr->Delete();
		return 0;
	}

	while (ptr->SwapScreen() == 0)
	{

	}
	return 0;
}