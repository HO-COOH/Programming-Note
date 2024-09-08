#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/embed.h>

int main()
{
	pybind11::scoped_interpreter guard{};

	pybind11::print(pybind11::int_{ 1 } + pybind11::int_{ 2 });
	
	auto plt = pybind11::module::import("matplotlib.pyplot");
	auto np = pybind11::module::import("numpy");

	auto x = np.attr("linspace")(0, 2 * np.attr("pi").cast<double>(), 200);
	auto y = np.attr("sin")(x);

	auto ax = plt.attr("subplots")().cast<pybind11::tuple>()[1];
	ax.attr("plot")(x, y);
	plt.attr("show")();

	std::cin.get();
}