#pragma once

namespace CommonLibrary
{
	/// <summary>
	/// シングルトンパターンのテンプレート
	/// </summary>
	template <class T>
	class Singleton
	{
	public:
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <remarks>
		/// 唯一のインスタンスが生成されていない場合はアクセス時に生成される。
		/// </remarks>
		/// <returns>インスタンス</returns>
		static T* Instance()
		{
			if (ms_Instance == nullptr)
			{
				ms_Instance = new T();
			}
			return ms_Instance;
		}

		/// <summary>
		/// インスタンスの明示的削除
		/// </summary>
		static void ResetSingleton()
		{
			if (ms_Instance == nullptr)return;
			delete ms_Instance;
			ms_Instance = nullptr;
		}

		/// <summary>
		/// インスタンスが適切に生成されているかを取得
		/// </summary>
		/// <returns>すでにインスタンスが生成されている場合はtrueを返す</returns>
		static bool Exist()
		{
			return ms_Instance != nullptr;
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