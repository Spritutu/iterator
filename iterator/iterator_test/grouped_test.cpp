using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <vector>
#include <numeric>

#include <iterator/grouped.h>

#include "vector_test.h"

namespace iterator_test
{		
	TEST_CLASS(GroupedUnitTest)
	{
	public:

		template<unsigned int N>
		void LoopCountCheck(int list_size)
		{
			int group_size = N;
			int group_count = list_size / group_size;
			if (list_size % group_size != 0){
				++group_count;
			}
			auto v = GetList(list_size);
			int i = 0;
			for (const auto &items : iterator::Grouped<N>(v)){
				int j = 0;
				for (const auto &item : items){
					++j;
				}
				Assert::AreEqual(group_size, j, L"unmatch group size");
				++i;
			}
			Assert::AreEqual(group_count, i, L"unmatc group count");
		}

		TEST_METHOD(IndexIteratorTest)
		{
			auto list = GetList(9);
			auto begin = iterator::Index<int>(list.data());
			auto end = iterator::Index<int>(list.data() + list.size());

			std::vector<int> result;
			for (auto i = begin; i != end; ++i){
				result.push_back(*i);
			}
			ListTest(list, result);
		}

		TEST_METHOD(RangeTest)
		{
			auto list = GetList(9);
			auto begin = iterator::Index<int>(list.data());
			auto end = iterator::Index<int>(list.data() + list.size());

			std::vector<int> result;
			for (const auto &item : iterator::Range<int, 9>(list.data())){
				result.push_back(item);
			}
			ListTest(list, result);
		}

		TEST_METHOD(OffsetIteratorTest)
		{
			const int group_size = 3;

			auto list = GetList(9);
			auto begin = iterator::Offset<int, group_size>(list.data());

			auto size = list.size();
			if (size % group_size != 0){
				throw;
			}
			size = size / group_size;
			auto end = iterator::Offset<int, group_size>(list.data() + size * group_size);

			std::vector<int> result;
			for (auto i = begin; i != end; ++i){
				for (const auto &item : *i){
					result.push_back(item);
				}
				result.push_back(0);
			}
			std::vector<int> expected = { 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0 };
			ListTest(expected, result);
		}

		TEST_METHOD(GroupedTest)
		{
			auto v = GetList(9);
			std::vector<int> result;
			for (const auto &items : iterator::Grouped<3>(v)){
				for (const auto &item : items){
					result.push_back(item);
				}
				result.push_back(0);
			}
			std::vector<int> expected = { 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0 };
			ListTest(expected, result);
		}

	};
}
