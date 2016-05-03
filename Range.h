#ifndef RANGE_H
#define RANGE_H

#include <type_traits>
#include <iterator>


namespace rg
{

template <typename T, typename U>
class Range
{
public:


	using Type = decltype(std::declval<T>() + std::declval<U>());

	using Step = U;



	Range (const Type& begin, const Type& end, const Step& step) : begin_(begin), end_(end), step_(step) {}

	Range (const Type& begin, const Type& end) : begin_(begin), end_(end), step_(Step{1}) {}

	Range (const Type& end) : begin_(Type{}), end_(end), step_(Step{1}) {}



	class Iterator : public std::iterator<std::forward_iterator_tag, T>
	{
    public:

    friend class Range;


    	Iterator (const Type& index = Type{}, const Step& step = Step{1}) : index(index), step(step) {}


		inline Type& operator * () { return index; }

		inline const Type& operator * () const { return index; }


		inline const Iterator& operator ++ () { index += step; return *this; }

		inline Iterator operator ++ (int) { Iterator ret(*this); this->operator++(); return ret; }



		inline bool operator < (const Iterator& it) const { return step > 0 ? index < it.index : index > it.index; }

		///// ---- GAMB  ----   /////

		inline bool operator == (const Iterator& it) const { return !(*this < it); }

		inline bool operator != (const Iterator &it) const { return !(*this == it); }

		///// ---- GAMB  ----   /////


	private:

		Type index;

		Step step;

   };




   inline Iterator begin() const { return Iterator(begin_, step_); }


   inline Iterator end() const { return Iterator(end_, step_); }



//private:

	Type begin_;

	Type end_;

	Step step_;


};


template <typename T, typename U>
inline decltype(auto) range (const T& begin, const T& end, const U& step)
{
	return Range<T, U>(begin, end, step);
}

template <typename T>
inline decltype(auto) range (const T& begin, const T& end)
{
	return Range<T, T>(begin, end);
}

template <typename T>
inline decltype(auto) range (const T& end)
{
	return Range<T, T>(end);
}



}	// namespace rg


#endif // RANGE_H