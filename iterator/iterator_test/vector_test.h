# pragma once

#include <vector>

namespace iterator_test
{

	std::vector<int> GetList(int count);

	template<class List>
	void ListTest(const List &expected, const List &result){
		for (unsigned int i = 0; i < result.size(); ++i){
			auto text = std::to_wstring(i) + L"is bad parameter";
			Assert::AreEqual(expected.at(i), result.at(i), text.c_str());
		}
		Assert::AreEqual(expected.size(), result.size(), L"unexpected list size");
	}

}
