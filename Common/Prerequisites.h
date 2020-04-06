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
#include <cassert>


// アトミック型の再定義
using S8 = std::int8_t;
using S16 = std::int16_t;
using S32 = std::int32_t;
using S64 = std::int64_t;
using U8 = std::uint8_t;
using U16 = std::uint16_t;
using U32 = std::uint32_t;
using U64 = std::uint64_t;

using Byte = unsigned char;

using F32 = float;
using F64 = double;

// 文字列型の再定義
using String = std::wstring;

// コンテナの再定義
template<class Key, class T>
using HashMap = std::unordered_map<Key, T>;

template<class Key, class T>
using HashSet = std::unordered_set<Key, T>;

template<class T>
using ArrayList = std::vector<T>;

template<class T>
using Queue = std::queue<T>;

template<class T>
using Stack = std::stack<T>;


// スマートポインタの再定義
#define MSPtr std::make_shared
#define MUPtr std::make_unique

template<class T>
using SPtr = std::shared_ptr<T>;
template<class T>
using UPtr = std::unique_ptr<T>;
template<class T>
using WPtr = std::weak_ptr<T>;