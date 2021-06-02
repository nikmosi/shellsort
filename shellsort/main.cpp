#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include "omp.h"

using namespace std::chrono;

void shell_sort(std::vector<int> &arr)
{
   size_t d = (arr.size() + 1) / 2;
   for(; d >= 1; d /= 2)
   {
      int s = arr.size() - d;
#pragma omp parallel for shared(arr)
      for(int i = 0; i < s; ++i)
         for(int p = i + d; p >= d && arr[p] < arr[p - d]; p -= d)
            std::swap(arr[p], arr[p - d]);
   }
}

int main(int argc, char *argv[])
{
   int r = 1, c = 1;

   std::cout << "Number of values: ";
   std::cin >> c;

   std::cout << "Number of threads: ";
   std::cin >> r;

   omp_set_num_threads(r);

   std::vector<int> a(c);
   for(int i = c; --i >= 0;) a[i] = c - i;

   std::copy(a.cbegin(), a.cend(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;

   const auto s = high_resolution_clock::now();
   shell_sort(a);
   auto t = duration_cast<duration<double, std::ratio<1>>>(high_resolution_clock::now() - s).count();

   std::copy(a.cbegin(), a.cend(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << ": " << t << " ms." << std::endl;

   return 0;
}
