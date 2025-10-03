#include <iostream>
#include <vector>
#include <sstream>
#include <string>     // For std::string
#include <algorithm>  // For std::transform
#include <cctype>     // For ::tolower
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <functional> // Required for std::greater<>
#include <bitset>

class ScalingSqStrings
{
public:
    static std::string scale(const std::string &strng, int k, int v) {

        std::vector<std::string> tokens = split_string_by_newline(strng);
        std::stringstream final_stream;

        for(const auto& token : tokens) {
           std::string scaled_horizontally = multiply_chars(token, k);
           for(int i=0; i < v; ++i) {
               final_stream << scaled_horizontally << '\n';
            }
        }

        std::string final_result = final_stream.str();
        // remove the trailing line
        if(!final_result.empty()) {
            final_result.pop_back();
        }
        return final_result;
    }

private:
    static std::vector<std::string> split_string_by_newline(const std::string& input) {

        std::vector<std::string> tokens;
        std::stringstream ss(input);
        std::string line;
        while(std::getline(ss, line)) {
           tokens.push_back(line);
        }
        return tokens;
    }

    static std::string multiply_chars(const std::string& token, int k) {

        std::string result;



        result.reserve(token.length() * k);
        for (char c : token) {
            result.append(k, c);
        }
        return result;
    }
};

std::vector<int> climb(int n)
{
    if (n < 1) return {};

    std::vector<int> path;
    int current = n;

    while (current > 1) {
        path.push_back(current);

        // if current is odd it came from 2*x+1
        if (current & 1) {
            current = (current - 1) / 2;
        }
        else {
            current = current / 2;
        }
    }
    path.push_back(1);

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector <int> solve(std::vector<int> array) {
  std::vector<int> dominants;
  bool dominant = true;
  for (size_t i=0; i<array.size(); i++) {
      for (size_t j=array.size()-1; j>i; j--) {
          if (array[i] < array[j]) {
              dominant = false;
          }
      }
    if (std::find(dominants.begin(), dominants.end(), array[i]) == dominants.end() && dominant == true) {
        dominants.push_back(array[i]);
        }
    dominant = true;
  }
  return dominants;
}

int even_last(std::vector<int> nums) {

 if (nums.empty()) {
     return 0;
 }

 int sum_at_even_indices = 0;

 for (size_t i = 0; i < nums.size(); i += 2) {
     sum_at_even_indices +=  nums[i];
 }

 return sum_at_even_indices * nums.back();
}

int makeNegative(int num) {
    return -std::abs(num); // #include <cmath>
}

std::string to_lowercase(const std::string& in) {
    // Create a new string with the same size as the input.
    // This pre-allocates the memory and is highly efficient.
    std::string out(in.size(), ' ');
    // ' ':  is the second argument. It's the character that will be used to initialize all the pre-allocated spots.

    /**
     * Single Memory Allocation: By creating the output string out with the correct size from the start (in.size()),
     * you prevent the performance cost of repeated memory reallocations that would happen if you built the string
     * character by character with push_back.
     */
    // Transform the input string to lowercase and store it in the output string.
    /**
      Direct Iteration: std::transform uses iterators to work directly on the strings' underlying character buffers, which is as fast as a manual for loop.
     */
    std::transform(in.begin(), in.end(), out.begin(), ::tolower);

    return out;
}

std::size_t duplicateCount(const std::string& in)
{
    std::string lower(to_lowercase(in));
    std::unordered_map<char, size_t> freq;
    int duplicate_count = 0;

    for(char ch: lower) {
        freq[ch]++;
    }

    for (const auto& pair : freq) {
        if (pair.second > 1) {
            duplicate_count++;
        }
    }

    return duplicate_count;
}

int string_to_number(const std::string& s) {
  //your code here
  return 1;
}

std::vector<int> menFromBoys(std::vector<int> values)
{
    // 1. Remove duplicates efficiently
    std::unordered_set<int> unique_elements(values.begin(), values.end());
    // 2. Containers for sorting
    // odds: sorted descending (std::greater)
    std::set<int, std::greater<int>> odds;
    // evens: sorted ascending (std::less, the default)
    std::set<int> evens; // No need for std::less<int> explicitly

    // 3. Populate sets (O(N log N) total)
    for (const int& el : unique_elements) {
        if (el % 2 == 0) {
            evens.insert(el);
        } else {
            odds.insert(el);
        }
    }
    std::vector<int> final_vec(evens.begin(), evens.end());

    final_vec.insert(final_vec.end(), odds.begin(), odds.end());

    return final_vec;
}

std::vector<int> menFromBoysII(std::vector<int> values)
{
    // 1. Partition (Separate Evens from Odds)
    // std::partition moves all elements for which the lambda returns 'true' (Evens)
    // to the beginning of the vector. 'it' points to the first Odd number.
    // Time Complexity: O(N)
    auto it = std::partition(values.begin(), values.end(), [](int n) {
        return n % 2 == 0;
    });

    // 2. Sort the Evens (ascending)
    // The range [begin(values), it) contains all the Evens.
    // Time Complexity: O(N_Evens * log(N_Evens)) -> O(N log N) worst-case
    std::sort(values.begin(), it);

    // 3. Sort the Odds (descending)
    // The range [it, end(values)) contains all the Odds.
    // Time Complexity: O(N_Odds * log(N_Odds)) -> O(N log N) worst-case
    std::sort(it, values.end(), std::greater<int>());

    // 4. Remove Duplicates
    // std::unique moves all duplicates to the end of the range.
    // It returns an iterator to the new logical end (iNewEnd).
    // Time Complexity: O(N)
    auto iNewEnd = std::unique(values.begin(), values.end());

    // 5. Erase the Duplicates
    // Physically removes the duplicated elements from the vector.
    // Time Complexity: O(N) (due to element shifting)
    values.erase(iNewEnd, values.end());

    return values;
}

unsigned int reverse_bits(unsigned int n) {
  std::string str = std::bitset<8>(n).to_string();
  std::reverse(str.begin(), str.end());
  int i = std::stoi(str, nullptr, 2);
  std::cout << i << std::endl;
  return i;
}

int main () {

   //for (const auto& i: container) {
      //std::cout << i << ' ';
   //}
   reverse_bits(417);
   solve({1, 21, 4, 7, 5});
   return 0;
}
