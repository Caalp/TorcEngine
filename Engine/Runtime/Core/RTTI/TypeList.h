#pragma once
#include <type_traits>

namespace Torc
{
	class NullType
	{};

	template<class A, class B = NullType>
	struct TypeList
	{
		typedef A type;
		typedef B rest;
	};

	template<class T0 = NullType, class T1 = NullType, class T2 = NullType, class T3 = NullType, class T4 = NullType, class T5 = NullType>
	class BuildTypeList
	{
	private:
		typedef typename BuildTypeList<T1, T2, T3, T4, T5>::Result R1;
	public:
		typedef TypeList<T0, R1> Result;
	};

	template<>
	class BuildTypeList<NullType>
	{
	public:
		typedef NullType Result;
		typedef NullType Type;
	};

	template<class A>
	struct GetLength;

	template<>
	struct GetLength<NullType>
	{
		static const int count = 0;
	};

	template<class A, class B>
	struct GetLength<TypeList<A, B>>
	{
		static const int count = 1 + GetLength<B>::count;
	};

	template<class A, class B>
	struct HasType
	{
		static const bool value = HasType<A,
			typename std::conditional<std::is_same_v<A, typename B::type>, NullType,
			typename std::conditional < std::is_same_v<typename B::rest, NullType>, A, typename B::rest > ::type > ::type > ::value;
	};

	template<class A>
	struct HasType<A, NullType>
	{
		static const bool value = true;
	};

	template<class A>
	struct HasType < A, A>
	{
		static const bool value = false;
	};

	template<class A, class B>
	struct GetTypeIndex
	{
		static const int value = (HasType<A, B>::value) ?
			1 + GetTypeIndex<A, typename std::conditional<!std::is_same_v<A, typename B::type>, typename B::rest, NullType>::type>::value : -1;
	};

	template<class A>
	struct GetTypeIndex<A, NullType>
	{
		static const int value = -1;
	};

	// AppendType
	template<class TList, class NewType>
	struct Append;

	template<class A, class NewType>
	struct Append<TypeList<A, NullType>, NewType>
	{
		typedef TypeList<A, TypeList<NewType, NullType>> Result;
	};

	template<class A, class TRest, class NewType>
	struct Append<TypeList<A, TRest>, NewType>
	{
		typedef TypeList<A, typename Append<TRest, NewType>::Result> Result;
	};

	// GetTypeAt
	template<class TList, int index>
	struct GetTypeAt;

	template<class THead, class TRest>
	struct GetTypeAt<TypeList<THead, TRest>, 0>
	{
		typedef THead Result;
	};

	template<int index>
	struct GetTypeAt<NullType, index>
	{
		typedef NullType Result;
	};

	template<class THead, class TRest, int index>
	struct GetTypeAt<TypeList<THead, TRest>, index>
	{
		typedef typename GetTypeAt<TRest, index - 1>::Result Result;
	};

	// RemoveType
	template<class TList, class TType>
	struct RemoveType;

	template<class TType>
	struct RemoveType<NullType, TType>
	{
		typedef NullType Result;
	};

	template<class THead, class TRest, class TType>
	struct RemoveType<TypeList<THead, TRest>, TType>
	{
		typedef typename TypeList<THead, typename RemoveType<TRest, TType>::Result> Result;
	};

	template<class THead, class TRest>
	struct RemoveType<TypeList<THead, TRest>, THead>
	{
		typedef typename RemoveType<typename TRest, THead>::Result Result;
	};

	// NoDuplicates
	template<class TList, class NewTList = NullType>
	struct NoDuplicates;

	// initial condition
	template<class THead, class TRest>
	struct NoDuplicates<TypeList<THead, TRest>, NullType>
	{
	private:
		typedef TypeList <THead, NullType> NewList;
	public:
		typedef typename NoDuplicates<TRest, NewList>::Result Result;
	};

	template<class THead>
	struct NoDuplicates<TypeList<THead, NullType>, NullType>
	{
	private:
		typedef TypeList <THead, NullType> NewList;
	public:
		typedef typename NewList Result;
	};

	// termination conditions
	template<class THead, class NewTList>
	struct NoDuplicates<TypeList<THead, NullType>, NewTList>
	{
	private:
		typedef typename std::conditional<HasType<THead, NewTList>::value, NewTList, typename Append<NewTList, THead>::Result>::type NewList;
	public:
		typedef NewList Result;
	};


	// base case
	template<class THead, class TRest, class NewTList>
	struct NoDuplicates<TypeList<THead, TRest>, NewTList>
	{
	private:
		typedef typename std::conditional<HasType<THead, NewTList>::value, NewTList, typename Append<NewTList, THead>::Result>::type NewList;
	public:
		typedef typename NoDuplicates<TRest, NewList>::Result Result;
	};
}
