/**
* @file Prerequisites.h
* @brief すべてのファイルに共通して読み込むべきヘッダ。
* @details プリミティブ型のリネームやSTLのリネームを行う。通常API使用時はこちらではなくOrigamiAPI.hを読み込む。
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>

#include "Singleton.h"


namespace OrigamiEngine {

	// アトミック型の再定義
	typedef std::int8_t I8;
	typedef std::int16_t I16;
	typedef std::int32_t I32;
	typedef std::int64_t I64;
	typedef std::uint8_t U8;
	typedef std::uint16_t U16;
	typedef std::uint32_t U32;
	typedef std::uint64_t U64;

	typedef unsigned char Byte;

	typedef float F32;
	typedef double F64;
	
	typedef std::wstring String;

#define HashMap std::unordered_map
#define HashSet std::unordered_set
#define ArrayList std::vector

#define Queue std::queue
#define Stack std::stack

	




#define SPtr std::shared_ptr
#define UPtr std::unique_ptr
#define WPtr std::weak_ptr

#define MSPtr std::make_shared
#define MUPtr std::make_unique
		;
}

using namespace OrigamiEngine;