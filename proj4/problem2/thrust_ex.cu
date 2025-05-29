#include <chrono>
#include <iomanip>
#include <iostream>
#include <thrust/functional.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/transform_reduce.h>

namespace {
    struct Integrand
    {
        public:
            __host__ __device__ explicit Integrand(double aDx_)
                : _dx(aDx_)
            {}

            __host__ __device__ double operator()(const double aIdx) const
            {
                constexpr double mid = 0.5;
                double x = _dx * (aIdx + mid);
                return (4.0 / (1.0 + x * x)) * _dx;
            }

        private:
            double _dx;
    };
} // namespace

int main()
{
    constexpr unsigned long lastNumber = 100000000;
    const double dx = 1.0 / static_cast<double>(lastNumber);
    auto start = std::chrono::high_resolution_clock::now();
    thrust::counting_iterator<unsigned long> begin(0);
    thrust::counting_iterator<unsigned long> end(lastNumber);

    double result = thrust::transform_reduce(thrust::device, begin, end, Integrand(dx), 0.0, thrust::plus<double>());

    auto stop = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(stop - start).count();

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Execution Time : " << seconds << "sec" << "\n";
    std::cout << "pi=" << result << "\n";

    return 0;
}
