/**
* @file Singleton.h
*/
#pragma once

namespace CommonLibrary
{
	/**
	* @brief �V���O���g���p�^�[���̃e���v���[�g�B
	*/
	template <class T>
	class Singleton
	{
	public:
		/**
		* @brief �C���X�^���X�̎擾�B
		*/
		static T* Instance()
		{
			if (ms_Instance == nullptr)
			{
				ms_Instance = new T();
			}
			return ms_Instance;
		}

		/**
		* @brief �C���X�^���X�̖����I�폜�B
		*/
		static void ResetSingleton()
		{
			if (ms_Instance == nullptr)return;
			delete ms_Instance;
			ms_Instance = nullptr;
		}

		/**
		* @brief �C���X�^���X���K�؂ɐ�������Ă��邩���擾�B
		*/
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