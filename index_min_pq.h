#pragma once

#include <iostream>
#include <vector>



template <typename ElementType>
class IndexMinPQ
{
public:
	IndexMinPQ(uint32_t n);

	bool Empty() const;
	uint32_t Size() const;

	bool Contains(uint32_t i) const;
	ElementType At(uint32_t i) const;

	void Insert(uint32_t i, ElementType elem);
	uint32_t DelMin();

	void DecreaseElem(uint32_t i, ElementType new_elem);
	void IncreaseElem(uint32_t i, ElementType new_elem);
	void ChangeElem(uint32_t i, ElementType new_elem);

	void Remove(uint32_t i);

	void Print() const;

private:
	void ValidateIndex(uint32_t i) const;
	void Exch(uint32_t i, uint32_t j);

	void Swim(uint32_t k);	// Heap helper function
	void Sink(uint32_t k);	// Heap helper function

	uint32_t max_size_;		// Maximum number of elements on PQ
	uint32_t size_ = 0;		// Number of elements on PQ

	std::vector<int> pq_;	// Binary heap using 1-based indexing
	std::vector<int> qp_;	// Inverse of pq: qp[pq[i]] = pq[qp[i]] = i

	std::vector<ElementType> elements_;
};



