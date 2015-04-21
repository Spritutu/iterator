using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <vector>
#include <numeric>

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
				item.item_.get() = 3;
				item.index_ = 0;
			}

			std::vector<int> result_item;
			for (const auto &item : iterator::Enumerate(list)){
				result_item.push_back(item.item_);
			}

			std::vector<int> expected_item = { 3, 3, 3, 3, 3 };
			ListTest(expected_item, result_item);
		}

	};
}