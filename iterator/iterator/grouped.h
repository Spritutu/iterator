#pragma once

#include <iostream>
#include <vector>

namespace iterator
{

	template<class Type>
	class Index{
	public:
		Index(const Type *head){
			index_ = const_cast<Type*>(head);
		}
		bool operator !=(const Index<Type> &other) const{
			return index_ != other.index_;
		}
		Type operator *() const{
			return *index_;
		}
		void operator ++(){
			++index_;
		}
	private:
		Type *index_ = nullptr;
	};

	template<class Type>
	class Range{
	public:
		Range(const Type *begin, std::size_t size){
			begin_ = begin;
			size_ = size;
		}
		Index<Type> begin() const{
			return Index<Type>(begin_);
		}
		Index<Type> end() const{
			return Index<Type>(begin_ + size_);
		}
	private:
		const Type *begin_ = nullptr;
		std::size_t size_ = 0;
	};

	template<class Type, unsigned int N>
	class Offset{
	public:
		Offset(const Type *ptr){
			index_ = const_cast<Type*>(ptr);
		}
		bool operator !=(const Offset<Type, N> &foo) const{
			return index_ != foo.index_;
		}
		Range<Type> operator *() const{
			return Range<Type>(index_, N);
		}
		void operator ++(){
			index_ += N;
		}
	private:
		Type *index_ = nullptr;
	};

	template<class Type, unsigned int N>
	class GroupedIterator{
	public:
		GroupedIterator(const std::vector<Type> &list){
			begin_ = list.data();

			auto size = list.size();
			if (size % N != 0){
				throw;
			}
			size = size / N;

			end_ = list.data() + size * N;
		}
		Offset<Type, N> begin() const{
			return Offset<Type, N>(begin_);
		}
		Offset<Type, N> end() const{
			return Offset<Type, N>(end_);
		}
	private:
		const Type *begin_;
		const Type *end_;
	};

	template<unsigned int N, class Container>
	GroupedIterator<int, N> Grouped(const Container &list){
		return GroupedIterator<int, N>(list);
	}

}
