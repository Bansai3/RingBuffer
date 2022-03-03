namespace algo_space
{
	template<typename T1, typename T2>
	bool all_of(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		while (start_iterator != end_iterator + 1)
		{
			if (!predicate(*start_iterator))
				return false;
			start_iterator++;
		}
		return true;
	}

	template<typename T1, typename T2>
	bool any_of(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		while (start_iterator != end_iterator + 1)
		{
			if (predicate(*start_iterator))
				return true;
			start_iterator++;
		}
		return false;
	}

	template<typename T1, typename T2>
	bool none_of(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		while (start_iterator != end_iterator + 1)
		{
			if (predicate(*start_iterator))
				return false;
			start_iterator++;
		}
		return true;
	}

	template<typename T1, typename T2>
	bool one_of(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		int count = 0;
		while (start_iterator != end_iterator + 1)
		{
			if (predicate(*start_iterator))
				count++;
			if (count > 1)
				return false;
			start_iterator++;
		}
		if (count == 1)
			return true;
		else
			return false;
	}

	template<typename T1, typename T2>
	bool is_sorted(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		while (start_iterator != end_iterator)
		{
			if (!predicate(*start_iterator, *(start_iterator + 1))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T1, typename T2>
	bool is_partitioned(T1 start_iterator, T1 end_iterator, T2 predicate)
	{
		bool 
	}
}