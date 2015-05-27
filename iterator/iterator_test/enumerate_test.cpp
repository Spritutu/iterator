using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <vector>
#include <numeric>
#include <algorithm>

#include <iterator/iterator.h>

#include "vector_test.h"

namespace iterator_test
{
	TEST_CLASS(EnumerateUnitTest)
	{
	public:

		TEST_METHOD(EnumerateTest)
		{
			auto list = GetList(5);

			std::vector<int> result_index;
			std::vector<int> result_item;
			for (const auto &item : iterator::Enumerate(list)){
				result_index.push_back(item.index_);
				result_item.push_back(item.item_);
			}

			std::vector<int> expected_index = { 0, 1, 2, 3, 4 };
			ListTest(expected_index, result_index);

			std::vector<int> expected_item = { 1, 2, 3, 4, 5 };
			ListTest(expected_item, result_item);
		}

		TEST_METHOD(EnumerateWriteTest)
		{
			auto list = GetList(5);
			for (auto &item : iterator::Enumerate(list)){
				item.item_ = 3;
			}

			std::vector<int> result_item;
			for (const auto &item : iterator::Enumerate(list)){
				result_item.push_back(item.item_);
			}

			std::vector<int> expected_item = { 3, 3, 3, 3, 3 };
			ListTest(expected_item, result_item);
		}

		TEST_METHOD(EnumerateAlgorithmTest)
		{
			auto list = GetList(5);
			auto enumerate = iterator::Enumerate(list);
			auto find_iterator = std::find_if(enumerate.begin(), enumerate.end(), [](const iterator::EnumPair<int> &item){
				return item.index_ == 3;
			});
			Assert::AreEqual((*find_iterator).index_, 3u, L"unexpected index");
			Assert::AreEqual((*find_iterator).item_, 4, L"unexpected item value");
		}
	};
}
