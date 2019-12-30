/**
* @file Input.h
*/
#pragma once

#include "OrigamiAPI.h"



namespace OrigamiEngine {
	/**
	* @brief 入力システムのマネージャ。
	* @details マウス、キーボード、ゲームパッドの入力を検知する。入力に別名をつけることによって複数の入力をまとめて扱うこともできる。
	*/
	class Input :public Singleton<Input>
	{
		friend class Singleton<Input>;
	public:
		//! @brief マウスの左ボタンの番号
		static int LEFT;
		//! @brief マウスの右ボタンの番号
		static int RIGHT;
		//! @brief マウスの中ボタンの番号
		static int MIDDLE;

		/**
		* @brief 入力の更新処理。
		*/
		void Update();

		/**
		* @brief 指定したマウスのボタンの押されている時間を取得する。
		* @param num マウスのボタン坂東
		* @return おされている時間(ms)
		*/
		int GetMouseButtonPressedTime(const unsigned int num);


		static bool GetMouseHover(const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButton(const unsigned int num);
		static bool GetMouseButton(const unsigned int num, const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButtonDown(const unsigned int num);
		static bool GetMouseButtonDown(const unsigned int num, const int x1, const int y1, const int x2, const int y2);

		// GetAxis
		// GetButton
		// GetButtonDown
		// GetButtonUp
		// GetKey
		// GetKeyDown
		// GetKeyUp

	private:
		Input() :m_PressedTimes(8) {};
		ArrayList<int> m_PressedTimes;
	};
}