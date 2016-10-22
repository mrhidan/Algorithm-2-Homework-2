#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <bitset>
#include <queue> 
#include <string> 
#include <fstream>

size_t count_resulting_binclusters(std::unordered_set<std::string> &bins) {
    size_t cluster_count = 0;
    std::string tmpi;
    std::string tmpj;
    std::string tmp;
    std::queue<std::string> binq;
    while (!bins.empty()) {
        binq.push(*bins.begin());
        while (!binq.empty()) {
            tmp = binq.front();
            bins.erase(tmp);
            for (size_t i = 0; i < tmp.size(); ++i) {
                tmpi = tmp;
                tmpi[i] = tmpi[i] == '0' ? '1' : '0';
                if (bins.find(tmpi) != bins.end()) {
                    binq.push(tmpi);
                }
                for (size_t j = i + 1; j < tmpi.size(); ++j) {
                    tmpj = tmpi;
                    tmpj[j] = tmpj[j] == '0' ? '1' : '0';
                    if (bins.find(tmpj) != bins.end()) {
                        binq.push(tmpj);
                    }
                }
            }
            binq.pop();
        }
        ++cluster_count;
    }
    return cluster_count;
}

int main() {
    std::string filename = "data.txt"; //Your data file name
    std::fstream data(filename, std::ios_base::in);
    if (data.good()) {
        std::string raws;
        std::unordered_set<std::string> binstrings;
        size_t n, m;
        data >> n >> m;
        binstrings.reserve(n);
        for (int i = 0; i < n; ++i) {
            data >> raws;
            binstrings.insert(raws);
        }
        std::cout << count_resulting_binclusters(binstrings);
    }
    else {
        std::cout << filename + " is missing or damaged" << std::endl;
    }
    return 0;
}