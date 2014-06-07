#pragma once

namespace nameParser
{
	struct list
	{
		list *next;
		char key;
	};

	struct intList
	{
		intList *next;
		int key;
	};
}