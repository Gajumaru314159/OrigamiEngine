/**
* @file Prerequisites.h
* @brief すべてのファイルに共通して読み込むべきヘッダ。
* @details プリミティブ型のリネームやSTLのリネームを行う。通常API使用時はこちらではなくOrigamiAPI.hを読み込む。
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