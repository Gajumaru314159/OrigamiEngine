#pragma once

namespace CommonLibrary
{
	/// <summary>
	/// �V���O���g���p�^�[���̃e���v���[�g
	/// </summary>
	template <class T>
	class Singleton
	{
	public:
		/// <summary>
		/// �C���X�^���X�̎擾
		/// </summary>
		/// <remarks>
		/// �B��̃C���X�^���X����������Ă��Ȃ��ꍇ�̓A�N�Z�X���ɐ��������B
		/// </remarks>
		/// <returns>�C���X�^���X</returns>
		static T* Instance()
		{
			if (ms_Instance == nullptr)
			{
				ms_Instance = new T();
			}
			return ms_Instance;
		}

		/// <summary>
		/// �C���X�^���X�̖����I�폜
		/// </summary>
		static void ResetSingleton()
		{
			if (ms_Instance == nullptr)return;
			delete ms_Instance;
			ms_Instance = nullptr;
		}

		/// <summary>
		/// �C���X�^���X���K�؂ɐ�������Ă��邩���擾
		/// </summary>
		/// <returns>���łɃC���X�^���X����������Ă���ꍇ��true��Ԃ�</returns>
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