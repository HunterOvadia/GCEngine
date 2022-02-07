#pragma once
#include "../Memory/GCMemory.h"

template<typename TType>
class Array
{
public:
	Array();
	~Array();

	int Add(const TType& ToAdd);
	void Remove(const int Index);
	int Find(const TType& ToFind);
	void InsertAt(const int Index, const TType& ToInsert);

	void Clear();
	int GetCount();
	bool IsEmpty();
	TType* GetData();
	TType& operator[](const int Index);

private:
	bool DoesNeedToGrow();

private:
	TType* InternalStorage;
	int Count;

	size_t MemorySize;
};

template<typename TType>
inline Array<TType>::Array()
{
	Clear();
}

template<typename TType>
inline Array<TType>::~Array()
{
	Clear();
}

template<typename TType>
inline void Array<TType>::Clear()
{
	GCMemory::SafeFree(InternalStorage);

	Count = 0;
	MemorySize = 0;
}

template<typename TType>
inline int Array<TType>::Add(const TType& ToAdd)
{
	bool NeedToGrow = DoesNeedToGrow();
	if (NeedToGrow)
	{
		TType* OldStorage = InternalStorage;
		size_t OldSize = MemorySize;

		size_t NewAllocationSize = (sizeof(TType) * 3);
		InternalStorage = (TType*)GCMemory::Allocate(MemorySize + NewAllocationSize);

		GCMemory::Copy(InternalStorage, OldStorage, OldSize);

		MemorySize += NewAllocationSize;
	}

	TType* Destination = InternalStorage + Count;
	GCMemory::Copy(Destination, &ToAdd, sizeof(TType));
	++Count;

	return Count;
}

template<typename TType>
inline void Array<TType>::Remove(const int Index)
{
	if (Index > Count - 1)
	{
		// TODO(HO): Assert
		return;
	}

	if (Index != (Count - 1))
	{
		TType* Destination = InternalStorage + Index;
		TType* Source = InternalStorage + (Index + 1);

		size_t AmountToCopy = (Count - Index - 1) * sizeof(TType);
		GCMemory::Move(Destination, Source, AmountToCopy);
	}

	--Count;
}

template<typename TType>
inline int Array<TType>::Find(const TType& ToFind)
{
	int Result = -1;
	
	for (int Index = 0; Index < Count; ++Index)
	{
		if (ToFind == InternalStorage[Index])
		{
			Result = Index;
			break;
		}
	}

	return Result;
}

template<typename TType>
inline void Array<TType>::InsertAt(const int Index, const TType& ToInsert)
{
	GCMemory::Move(InternalStorage + (Index + 1), InternalStorage + Index, (Count - Index - 1) * sizeof(TType));
	InternalStorage[Index] = ToInsert;
	++Count;
}


template<typename TType>
inline int Array<TType>::GetCount()
{
	return Count;
}

template<typename TType>
inline bool Array<TType>::IsEmpty()
{
	return (Count == 0);
}

template<typename TType>
inline TType* Array<TType>::GetData()
{
	return nullptr;
}

template<typename TType>
inline TType& Array<TType>::operator[](const int Index)
{
	if (Index > (Count - 1))
	{
		// TODO(HO): Assert
	}

	return InternalStorage[Index];
}

template<typename TType>
inline bool Array<TType>::DoesNeedToGrow()
{
	return (sizeof(TType) * Count) >= MemorySize;
}
