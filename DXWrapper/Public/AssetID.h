#pragma once

namespace og
{
	template <class Type>
	class AssetID
	{
	public:
		using ValueType = S32;

		inline static const ValueType InvalidID = Largest<ValueType>;

	private:

		ValueType m_Value = InvalidID;

	public:

		constexpr AssetID() = default;

		explicit constexpr AssetID(ValueType id) noexcept : m_Value(id)
		{
		}

		constexpr ValueType Get() const noexcept
		{
			return m_Value;
		}

		constexpr bool isValid() const noexcept
		{
			return m_Value != InvalidID;
		}

		constexpr bool operator ==(const AssetID& other) const noexcept
		{
			return m_Value == other.m_Value;
		}

		constexpr bool operator !=(const AssetID& other) const noexcept
		{
			return m_Value != other.m_Value;
		}

		explicit operator bool() const noexcept { return isValid(); }
	};
}