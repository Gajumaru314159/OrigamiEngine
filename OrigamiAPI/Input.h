/**
* @file Input.h
*/
#pragma once

#include "Prerequisites.h"



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
		static S32 LEFT;
		//! @brief マウスの右ボタンの番号
		static S32 RIGHT;
		//! @brief マウスの中ボタンの番号
		static S32 MIDDLE;

		/**
		* @brief 入力の更新処理。
		*/
		void Update();

		/**
		* @brief 指定したマウスのボタンの押されている時間を取得する。
		* @param num マウスのボタン坂東
		* @return おされている時間(ms)
		*/
		S32 GetMouseButtonPressedTime(const U32 num);


		static bool GetMouseHover(const S32 x1, const S32 y1, const S32 x2, const S32 y2);
		static bool GetMouseButton(const U32 num);
		static bool GetMouseButton(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2);
		static bool GetMouseButtonDown(const U32 num);
		static bool GetMouseButtonDown(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2);

		// GetAxis
		// GetButton
		// GetButtonDown
		// GetButtonUp
		// GetKey
		// GetKeyDown
		// GetKeyUp

	private:
		Input() :m_PressedTimes(8) {};
		ArrayList<S32> m_PressedTimes;
	};
}