/**
* @file Prerequisites.h
* @brief ���ׂẴt�@�C���ɋ��ʂ��ēǂݍ��ނׂ��w�b�_�B
* @details �v���~�e�B�u�^�̃��l�[����STL�̃��l�[�����s���B�ʏ�API�g�p���͂�����ł͂Ȃ�OrigamiAPI.h��ǂݍ��ށB
*/

#pragma once
#pragma warning(push)
#pragma warning(disable:4251)

#include "Fwd.h"

#include "Check.h"
#include "Singleton.h"
#include "CustomString.h"
#include "Rect.h"
#include "Path.h"
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
#include "Number.h"
#include "Matrix.h"
#include "Mathf.h"
#include "Quaternion.h"


#ifndef USE_COMMONLIBRARY_NAMESPACE
using namespace CommonLibrary;
#endif

#pragma warning(pop)