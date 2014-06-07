#pragma once

namespace CellAuto
{
	class state
	{
		int stat;
	public:
		state(void);
		state(int);
		~state(void);
		operator int() {return stat;}
		int	operator=	(const int&);
		int	operator==	(const int&);
	};
}