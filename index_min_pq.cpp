#include "index_min_pq.h"
#include <cassert>
#include <stdexcept>

using namespace std;



template <typename ElementType>
IndexMinPQ<ElementType>::IndexMinPQ(uint32_t n)
	: max_size_ {n}
	, pq_(max_size_ + 1, 0)
	, qp_(max_size_ + 1, -1)
	, elements_(max_size_ + 1, 0)
{}



template <typename ElementType>
bool IndexMinPQ<ElementType>::Empty() const
{
	return (size_ == 0);
}


template <typename ElementType>
uint32_t IndexMinPQ<ElementType>::Size() const
{
	return size_;
}



template <typename ElementType>
bool IndexMinPQ<ElementType>::Contains(uint32_t i) const
{
	ValidateIndex(i);
	return (qp_[i] != -1);
}



template <typename ElementType>
ElementType IndexMinPQ<ElementType>::At(uint32_t i) const
{
	ValidateIndex(i);
	if ( !Contains(i) )
		throw runtime_error("Index is not in the priority queue!");
	return elements_[i];
}



template <typename ElementType>
void IndexMinPQ<ElementType>::Insert(uint32_t i, ElementType elem)
{
	ValidateIndex(i);
	if ( Contains(i) )
		throw runtime_error("Index is already in the priority queue!");
	qp_[i] = ++size_;
	pq_[size_] = i;
	elements_[i] = elem;
	Swim(size_);
}



template <typename ElementType>
uint32_t IndexMinPQ<ElementType>::DelMin()
{
	if ( size_ == 0 )
		throw runtime_error("Priority queue underflow!");
	int min = pq_[1];
	Exch(1, size_--);
	Sink(1);
	assert( min == pq_[size_+1] );
	qp_[min] = -1;
	pq_[size_+1] = -1;
	elements_[min] = 0;
//	elements_.erase
	return min;
}



template <typename ElementType>
void IndexMinPQ<ElementType>::DecreaseElem(uint32_t i, ElementType new_elem)
{
	ValidateIndex(i);
	if ( !Contains(i) )
		throw runtime_error("Index is not in the priority queue!");
	if ( new_elem >= elements_[i] )
		throw runtime_error("New_elem must be less than corresponding old elem!");
	elements_[i] = new_elem;
	Swim(qp_[i]);
}



template <typename ElementType>
void IndexMinPQ<ElementType>::ChangeElem(uint32_t i, ElementType new_elem)
{
	ValidateIndex(i);
	if ( !Contains(i) )
		throw runtime_error("Index is not in the priority queue!");
	elements_[i] = new_elem;
	Swim(qp_[i]);
	Sink(qp_[i]);
}



template <typename ElementType>
void IndexMinPQ<ElementType>::Print() const
{
/*	for ( auto x: pq_ )  cout << x << " ";
	cout << '\n';
	for ( auto x: qp_ )  cout << x << " ";
	cout << '\n';
	for ( auto x: elements_ )  cout << x << " ";
	cout << '\n'; */
	if ( Empty() )
		cout << "The IndexMinPQ is empty";
	else
		for ( auto i: pq_ )
			if ( i > 0 )  cout << "(" << i << ", " << elements_[i] << ") ";
	cout << '\n';
}



template <typename ElementType>
void IndexMinPQ<ElementType>::ValidateIndex(uint32_t i) const
{
	if ( i >= max_size_ )  // Must be 0 <= i < max_size_
		throw runtime_error("Index >= capacity!");
}



template <typename ElementType>
void IndexMinPQ<ElementType>::Exch(uint32_t i, uint32_t j)
{
	int temp = pq_[i];
	pq_[i] = pq_[j];
	pq_[j] = temp;
	qp_[pq_[i]] = i;
	qp_[pq_[j]] = j;
}



template <typename ElementType>
void IndexMinPQ<ElementType>::Swim(uint32_t k)
{
	while ( k > 1 && elements_[pq_[k/2]] > elements_[pq_[k]] )
	{
		Exch(k, k/2);
		k /= 2;
	}
}



template <typename ElementType>
void IndexMinPQ<ElementType>::Sink(uint32_t k)
{
	while ( 2*k <= size_ )
	{
		uint32_t j = 2*k;
		if ( j < size_ && elements_[pq_[j]] > elements_[pq_[j+1]] )  ++j;
		if ( !(elements_[pq_[k]] > elements_[pq_[j]]) )  break;
		Exch(k, j);
		k = j;
	}
}



template class IndexMinPQ<uint32_t>;
template class IndexMinPQ<float>;
template class IndexMinPQ<double>;
