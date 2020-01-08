/**
* @file Singleton.h
*/
#pragma once

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
		static T& GetInstance()
		{
			static typename T::singleton_poS32er_type s_singleton(T::createInstance());

			return getReference(s_singleton);
		}

	private:
		typedef std::unique_ptr<T> singleton_poS32er_type;

		inline static T* createInstance() { return new T(); }

		inline static T& getReference(const singleton_poS32er_type& ptr) { return *ptr; }

	protected:
		Singleton() {}

	private:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	};
}