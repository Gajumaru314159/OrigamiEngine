/**
* @file
*/

#pragma once

namespace og
{
	class Deletable
	{
	public:
		virtual void Delete() { delete this; }
	};
}


namespace std
{
	template <>
	struct default_delete<og::Deletable>
	{
		void operator()(og::Deletable* p) const
		{
			p->Delete();
		}
	};
}