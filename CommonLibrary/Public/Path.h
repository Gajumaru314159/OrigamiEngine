#pragma once

#include "Fwd.h"
#include "CustomString.h"

namespace CommonLibrary
{
	/// <summary>
	/// ファイルまたはディレクトリのパス情報を格納する
	/// </summary>
	class DLL Path
	{
	public:
		/// <summary>
		/// パスオブジェクトの生成
		/// </summary>
		/// <param name="path">パス文字列</param>
		Path(const String& path);

		/// <summary>
		/// 既存のパスを破棄して新しくパスを割り当てる
		/// </summary>
		/// <param name="path">パス文字列</param>
		/// <returns></returns>
		S32 Set(const String& path);

		/// <summary>
		/// パスオブジェクトからファイル名を取得する
		/// </summary>
		/// <returns>ファイル名またはディレクトリ名</returns>
		String FileName()const;

		/// <summary>
		/// パスオブジェクトからファイルの拡張子を取得する
		/// </summary>
		/// <returns>ファイルの拡張子。ディレクトリや拡張子のないファイルの場合はから文字列を返す。</returns>
		String Extension()const;

		/// <summary>
		/// パスオブジェクトが拡張子を含むかどうかを判定する
		/// </summary>
		/// <returns>パスオブジェクトが拡張子を含むならtrueを返す</returns>
		bool HasExtention()const;

		/// <summary>
		/// パスオブジェクトからフルパスを取得する
		/// </summary>
		/// <returns>フルパス</returns>
		String Fullpath()const;

		/// <summary>
		/// ファイルを含んでいるディレクトリのパスを取得する
		/// </summary>
		/// <returns>ディレクトリのパス</returns>
		String Directory()const;

		/// <summary>
		/// パスが適切で含むことのできない文字を含んでいないか
		/// </summary>
		/// <returns></returns>
		inline bool IsValid()const { return m_Path.size() != 0; };

		/// <summary>
		/// パスオブジェクトをString型に変換する
		/// </summary>
		/// <returns></returns>
		const String& ToString() const { return m_Path; }
	private:
		String m_Path;
		bool m_HasExtention;
	};
}