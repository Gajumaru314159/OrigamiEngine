/**
* @file Prerequisites.h
* @brief ���ׂẴt�@�C���ɋ��ʂ��ēǂݍ��ނׂ��w�b�_�B
* @details �v���~�e�B�u�^�̃��l�[����STL�̃��l�[�����s���B�ʏ�API�g�p���͂�����ł͂Ȃ�OrigamiAPI.h��ǂݍ��ށB
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


// �A�g�~�b�N�^�̍Ē�`
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

// ������^�̍Ē�`
using String = std::wstring;

// �R���e�i�̍Ē�`
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


// �X�}�[�g�|�C���^�̍Ē�`
#define MSPtr std::make_shared
#define MUPtr std::make_unique

template<class T>
using SPtr = std::shared_ptr<T>;
template<class T>
using UPtr = std::unique_ptr<T>;
template<class T>
using WPtr = std::weak_ptr<T>;