#pragma once

#include <cstdint>

namespace iterator
{

	template<class Type>
	struct EnumPair{
		EnumPair(std::uint32_t index, Type &item):
			index_(index),
			item_(item)
		{}
		const std::uint32_t index_ = 0;
		std::reference_wrapper<Type> item_;
	};

	template<class Type>
	class EnumerateIterator{
	public:
		EnumerateIterator(Type *head) :head_(head){
		}
		bool operator !=(const EnumerateIterator<Type> &other) const{
			return head_ + index_ != other.head_ + other.index_;
		}
		EnumPair<Type> operator *() const{
			EnumPair<Type> pair = {
				index_,
				std::ref(*(head_ + index_))
			};
			return pair;
		}
		void operator ++(){
			++index_;
		}
	private:
		Type *head_ = nullptr;
		unsigned int index_ = 0;
	};

	template<class Type>
	class EnumerateRange{
	public:
		EnumerateRange(Type *begin, std::size_t size){
			begin_ = begin;
			size_ = size;
		}
		EnumerateIterator<Type> begin() const{
			return EnumerateIterator<Type>(begin_);
		}
		EnumerateIterator<Type> end() const{
			return EnumerateIterator<Type>(begin_ + size_);
		}
	private:
		Type *begin_ = nullptr;
		std::size_t size_ = 0;
	};

	template<class List>
	auto Enumerate(List &list)->EnumerateRange <typename List::value_type >{
		return EnumerateRange<typename List::value_type>(list.data(), list.size());
	}
}