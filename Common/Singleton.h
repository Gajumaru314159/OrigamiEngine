/**
* @file Singleton.h
*/
#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief シングルトンパターンのテンプレート。
	*/
	template <class T>
	class Singleton
	{
	public:
		/**
		* @brief インスタンスの取得。
		*/
		static T* Create() {
			if (ms_Instance == nullptr) {
				ms_Instance = new T();
			}
			return ms_Instance;
		}

		/**
		* @brief インスタンスの明示的削除。
		*/
		void Destroy() {
			delete ms_Instance;
			ms_Instance = nullptr;
		}

		/**
		* @brief インスタンスが適切に生成されているかを取得。
		*/
		static bool Exist() {
			return ms_Instance!=nullptr;
		}

	protected:
		static T* ms_Instance;

		Singleton() {};
		virtual ~Singleton() {};

	private:

		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	};

	template <class T>
	T* Singleton<T>::ms_Instance = nullptr;
}