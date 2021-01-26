#include "Heap.h"

Heap::Heap() {}
void Heap::shift_down(int index) {
	while (2*index + 1 < sequence.size()) {
		int succ = 2 * index + 1;
		if (succ < sequence.size() - 1 && sequence[succ].e > sequence[succ + 1].e) {
			++succ;
		}
		if (sequence[index].e > sequence[succ].e) {
			swap(sequence[index], sequence[succ]);
			index = succ;
		}
		else {
			break;
		}
	}
}
void Heap::shift_up(int index) {
	while ((index - 1) / 2 >= 0) {
		if (sequence[(index - 1) / 2].e > sequence[index].e) {
			swap(sequence[(index - 1) / 2], sequence[index]);
			index = (index - 1) / 2;
		}
		else {
			break;
		}
	}
}
Edge Heap::readMin() const {
	if (sequence.size() == 0) {
		throw logic_error("There are'nt elements in the sequence");
	}
	return sequence[0];
}
Edge Heap::popMin() {
	Edge minEl = sequence[0];
	swap(sequence[0], sequence[sequence.size() - 1]);
	sequence.pop_back();
	shift_down(0);
	return minEl;
}
void Heap::insert(Edge element) {
	sequence.push_back(element);
	shift_up(sequence.size() - 1);
}
//void Heap::replace(Edge remove, Edge newEl) {
//	if (remove.e > newEl.e) {
//		int findIndex = find_index_edge(remove.);
//		sequence[findIndex] = newEl;
//		shift_up(findIndex);
//	}
//	else if (remove.e < newEl.e) {
//		int findIndex = lower_bound(sequence.begin(), sequence.end(), remove) - sequence.begin();
//		sequence[findIndex] = newEl;
//		shift_down(findIndex);
//	}
//}
//void Heap::print() const {
//	for (Edge curr : sequence) {
//		cout << curr << " ";
//	}
//}