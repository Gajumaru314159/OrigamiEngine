// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "TabTest.h"


DLLTab::DLLTab() {
	m_TabName = L"DLLTab";
}

void DLLTab::OnGUI(ITabBuilder& tabBuilder) {
	tabBuilder.PlaceButton(0x1234214);
	tabBuilder.PlaceButton(0x1234214);
}


ITab* DLLTab::CreateInstance() {
	return new DLLTab();
}


ITab* CreateTab()
{
	return new DLLTab();
}