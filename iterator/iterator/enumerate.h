#pragma once

namespace iterator
{

	template<class Type>
	struct EnumPair{
		unsigned int index_ = 0;
		const Type *item_ = nullptr;
	};

	template<class Type>
	class EnumerateIterator{
	public:
		EnumerateIterator(const Type *head) :head_(head){
		}
		bool operator !=(const EnumerateIterator<Type> &other) const{
			return head_ + index_ != other.head_ + other.index_;
		}
		EnumPair<Type> operator *() const{
			EnumPair<Type> pair;
			pair.index_ = index_;
			pair.item_ = head_ + index_;
			return pair;
		}
		void operator ++(){
			++index_;
		}
	private:
		const Type *head_ = nullptr;
		unsigned int index_ = 0;
	};

	template<class Type>
	class EnumerateRange{
	public:
		EnumerateRange(const Type *begin, std::size_t size){
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
		const Type *begin_ = nullptr;
		std::size_t size_ = 0;
	};

	template<class List>
	auto Enumerate(const List &list)->EnumerateRange <typename List::value_type >{
		return EnumerateRange<typename List::value_type>(list.data(), list.size());
	}
}