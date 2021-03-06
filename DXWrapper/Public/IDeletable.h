﻿#pragma once

class IDeletable
{
public:
	virtual void Delete() { delete this; }

	virtual ~IDeletable() {};
};


namespace std
{
	template <>
	struct default_delete<IDeletable>
	{
		void operator()(IDeletable* p) const
		{
			p->Delete();
		}
	};
}