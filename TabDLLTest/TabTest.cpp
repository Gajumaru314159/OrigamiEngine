// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "TabTest.h"

ArrayList<DLLTab*> ptrLst;

DLLTab::DLLTab() {
	m_TabName = L"DLLTab";
}

void DLLTab::OnGUI(ITabBuilder& tabBuilder) {
	tabBuilder.PlaceButton(Color(1, 0, 0));
	tabBuilder.PlaceButton(Color(0, 1, 0));
	tabBuilder.PlaceButton(Color(0, 0, 1));
	tabBuilder.PlaceButton(Color(0, 0, 1));
}


ITab* DLLTab::CreateInstance()
{
	auto ptr = new DLLTab();
	ptrLst.push_back(ptr);
	return ptr;//new DLLTab();
}
void DLLTab::Delete() {
	delete this;
}

ITab* CreateTab()
{
	auto ptr = new DLLTab();
	ptrLst.push_back(ptr);
	return ptr;//new DLLTab();
}


void Init()
{
	auto ptr = new DLLTab();
	ptrLst.push_back(ptr);
}
void Finalize()
{
	for (auto ptr : ptrLst) {
		delete ptr;
	}
}