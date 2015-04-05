#include "vector_test.h"

#include <numeric>

namespace iterator_test
{

	std::vector<int> GetList(int count){
		std::vector<int> v(count);
		std::iota(v.begin(), v.end(), 1);
		return v;
	}

}
