#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Fitness {
  int hours;
  int id;
  int year;
  int month;
  Fitness() {
    hours = 0;
    id = 0;
    year = 0;
    month = 0;
  }
  Fitness(int h, int i, int y, int m) {
    hours = h;
    id = i;
    year = y;
    month = m;
  }
};

struct yearMonthHours {
  int year;
  int month;
  int hours;
  yearMonthHours(int y, int m, int h) : year(y), month(m), hours(h) {}
};

bool findInYMH(int year, vector<yearMonthHours> ymhArr) {
  for (auto i = ymhArr.begin(); i < ymhArr.end(); i++) {
    if (year == (*i).year) {
      return true;
    }
  }
  return false;
}

int main() {
  // TASK 1, STL7Mix8
  vector<Fitness> center;
  vector<yearMonthHours> ymh;
  //////////////////////// h  id year  m
  center.push_back(Fitness(2, 3, 2017, 2));
  center.push_back(Fitness(1, 1, 2018, 3));
  center.push_back(Fitness(3, 3, 2018, 9));
  center.push_back(Fitness(1, 2, 2018, 4));
  center.push_back(Fitness(3, 2, 2018, 5));
  center.push_back(Fitness(1, 2, 2019, 1));
  cout << "Input K: ";
  unsigned int K;
  cin >> K;
  {
    map<pair<int, int>, int> monthHoursMap; // Map of year-month to total hours
    for (auto i = center.begin(); i < center.end(); i++) {
      if ((*i).id == K) {
        pair<int, int> yearMonth = make_pair((*i).year, (*i).month);
        if (monthHoursMap.find(yearMonth) == monthHoursMap.end()) {
          monthHoursMap[yearMonth] = (*i).hours;
        } else {
          monthHoursMap[yearMonth] += (*i).hours;
        }
      }
    }

    map<int, pair<int, int>>
        yearHoursMap; // Map of year to minimum hours and month
    for (auto i = monthHoursMap.begin(); i != monthHoursMap.end(); i++) {
      int year = i->first.first;
      int month = i->first.second;
      int hours = i->second;
      if (yearHoursMap.find(year) == yearHoursMap.end() ||
          hours < yearHoursMap[year].first) {
        yearHoursMap[year] = make_pair(hours, month);
      }
    }

    if (yearHoursMap.size() == 0) {
      cout << "ID " << K << " not found." << endl;
      return -1;
    } else {
      for (auto i = yearHoursMap.begin(); i != yearHoursMap.end(); i++) {
        cout << i->second.first << " " << i->first << " " << i->second.second
             << endl;
      }
    }
  }

  // TASK 2, STL3Alg8
  vector<bool> V;
  K = 0;
  do {
    cout << "Input K > 0: ";
    cin >> K;
  } while (K <= 0);
  cout << "Input N for vector: ";
  int N;
  cin >> N;
  cout << "Input vector: " << endl;
  for (int i = 0; i < N; i++) {
    bool temp;
    cin >> temp;
    V.push_back(temp);
  }
  vector<bool>::reverse_iterator rIter;
  rIter = V.rbegin();
  cout << endl;
  vector<bool>::reverse_iterator it;
  it = search_n(V.rbegin(), V.rend(), K, 0);
  if (it != V.rend()) {
    cout << "Found " << K << " 0s at pos " << N - int(it - V.rbegin()) - K
         << endl;
    for (unsigned int i = 0; i < K; i++) {
      V.erase(--(it.base()));
    }
  } else {
    cout << "Not found." << endl;
  }
  for (auto i = V.begin(); i < V.end(); i++) {
    cout << *i << " ";
  }
  cout << endl;

  // TASK 3, STL5Assoc8
  std::vector<int> V3 = {7, 3, 8, 1, 6, 4, 2, 5};

  // Find min and max elements
  auto minmax = std::minmax_element(V.begin(), V.end());
  int min = *minmax.first;
  int max = *minmax.second;

  // Set for unique elemets of array
  std::set<int> S3(V3.begin(), V3.end());

  // Remove min and max
  S3.erase(min);
  S3.erase(max);

  // Print elements from biggest to least
  std::copy(S3.rbegin(), S3.rend(), std::ostream_iterator<int>(std::cout, " "));
  cout << endl;
  return 0;
}
