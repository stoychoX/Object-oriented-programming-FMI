#include "SubsetIter.h"

SubsetIter::SubsetIter(const int* arg, size_t size) : data{ arg }, size{ size }, subsets{ size + 1 } {

}

SubsetIter& SubsetIter::operator++() {
	if (subsets.contains(size + 1)) {
		subsets.clear();
		return *this;
	}

	++subsets;
	return *this;
}

std::ostream& operator<<(std::ostream& ofs, const SubsetIter& arg) {
	ofs << "{";
	for (size_t i = 0; i < arg.size; i++) {
		if (arg.subsets.contains(i)) {
			ofs << arg.data[i] << ", ";
		}
	}
	ofs << "}" << std::endl;

	return ofs;
}
