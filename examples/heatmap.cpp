#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;

	{
		double array[/*rows*/4][/*columns*/3] = {
			{1, 2, 3},
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33}
		};
		Figure fig("Heatmap from 2d array");
		fig.add(heatmap(&array).label("Heatmap"));
		fig.yReverse();
		fig.show();
	}

    return 0;
}