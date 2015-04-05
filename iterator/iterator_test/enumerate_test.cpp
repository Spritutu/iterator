#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <vector>
#include <numeric>

#include <iterator/iterator.h>

namespace iterator_test
{
	TEST_CLASS(EnumerateUnitTest)
	{
	public:

		std::vector<int> GetList(int count){
			std::vector<int> v(count);
			std::iota(v.begin(), v.end(), 1);
			return v;
		}

		template<class List>
		void ListTest(const List &expected, const List &result){
			for (unsigned int i = 0; i < result.size(); ++i){
				auto text = std::to_wstring(i) + L"is bad parameter";
				Assert::AreEqual(expected.at(i), result.at(i), text.c_str());
			}
			Assert::AreEqual(expected.size(), result.size(), L"unexpected list size");
		}

		TEST_METHOD(EnumerateTest)
		{
			auto list = GetList(5);

			std::vector<int> result_index;
			std::vector<int> result_item;
			for (const auto &item : iterator::Enumerate(list)){
				result_index.push_back(item.index_);
				result_item.push_back(*item.item_);
			}

			std::vector<int> expected_index = { 0, 1, 2, 3, 4 };
			ListTest(expected_index, result_index);

			std::vector<int> expected_item = { 1, 2, 3, 4, 5 };
			ListTest(expected_item, result_item);
		}

	};
}