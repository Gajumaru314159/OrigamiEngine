/**
* @file Path.h
*/

#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief ファイルまたはディレクトリのパス情報を格納する。
	*/
	class Path {
	public:
		/**
		* @brief パスオブジェクトの生成。
		* @param path パス文字列。
		*/
		Path(String path);

		/**
		* @brief 既存のパスを破棄して新しくパスを割り当てる。
		* @param path パス文字列。
		*/
		void Set(String path);

		/**
		* @brief パスオブジェクトからファイル名を取得する。
		* @return ファイル名またはディレクトリ名。
		*/
		String FileName();

		/**
		* @brief パスオブジェクトからファイルの拡張子を取得する。
		* @return ファイルの拡張子。ディレクトリや拡張子のないファイルの場合はから文字列を返す。
		*/
		String Extension();

		/**
		* @brief パスオブジェクトが拡張子を含むかどうかを判定する。
		* @return パスオブジェクトが拡張子を含むならtrueを返す。
		*/
		bool HasExtention();

		/**
		* @brief パスオブジェクトからフルパスを取得する。
		* @return フルパス。
		*/
		String Fullpath();

		/**
		* @brief ファイルを含んでいるディレクトリのパスを取得する。
		* @return ディレクトリのパス。
		*/
		String Directory();

		operator String() const { return m_Path; }
	private:
		String m_Path;
		bool m_HasExtention;
	};
}