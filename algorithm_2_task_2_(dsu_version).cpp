#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <bitset>
#include <queue> 
#include <string> 
#include <fstream>

class DSU {
public:
    DSU(size_t n) {
        parent.resize(n);
        rank.resize(n);
    }
    void MakeSet(size_t v) {
        parent[v] = v;
        rank[v] = 0;
        ++dsu_size;
    }

    size_t find_set(size_t v) {
        if (v == parent[v])
            return v;
        return find_set(parent[v]);
    }

    void Union(size_t a, size_t b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
            --dsu_size;
        }
    }

    size_t size() const {
        return dsu_size;
    }

private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
    size_t dsu_size = 0;
};

void binclustering_standard(DSU &binclusters, std::queue<unsigned int> &bin_queue,
    std::unordered_map<unsigned int, size_t> &binmap, const size_t &m) {
    while (!bin_queue.empty()) { // about 7-8 minutes
        unsigned int tmp = bin_queue.front();
        for (int i = 0; i < m; ++i) {
            unsigned int tmpi = tmp ^ (1 << i);
            if (binmap.find(tmpi) != binmap.end()) {
                binclusters.Union(binmap[tmp], binmap[tmpi]);
            }
            for (int j = i + 1; j < m; ++j) {
                unsigned int tmpj = tmpi ^ (1 << j);
                if (binmap.find(tmpj) != binmap.end()) {
                    binclusters.Union(binmap[tmp], binmap[tmpj]);
                }
            }
        }
        bin_queue.pop();
    }
}

void binclustering_shortened(DSU &binclusters, std::queue<unsigned int> &bin_queue,
    std::unordered_map<unsigned int, size_t> &binmap, const size_t &m) {
    while (!bin_queue.empty()) {
        unsigned int tmp = bin_queue.front();
        for (int i = 0; i < m; ++i) {
            unsigned int tmpi = tmp ^ (1 << i);
            if (binmap.find(tmpi) != binmap.end()) {
                binclusters.Union(binmap[tmp], binmap[tmpi]);
            }
            else {
                binmap[tmpi] = binmap[tmp];
            }
        }
        bin_queue.pop();
    }

}

int main() {
    std::string filename = "data.txt"; //Your data file name
    std::fstream data(filename, std::ios_base::in);
    if (data.good()) {
        std::string raws;
        std::queue<unsigned int> bin_queue;
        std::unordered_map<unsigned int, size_t> binmap;
        size_t n, m;
        data >> n >> m;
        DSU binclusters(n);
        binmap.reserve(n*m);
        for (int i = 0; i < n; ++i) {
            data >> raws;
            unsigned int rawi = std::stoll(raws, nullptr, 2);
            if (binmap.find(rawi) == binmap.end()) {
                binmap[rawi] = i;
                binclusters.MakeSet(i);
                bin_queue.push(rawi);
            }
        }
        //Only one algorithm should be choosen
        //binclustering_standard(binclusters, bin_queue, binmap, m);
        binclustering_shortened(binclusters, bin_queue, binmap, m);
        std::cout << binclusters.size();
    }
    else {
        std::cout << filename + " is missing or damaged" << std::endl;
    }
    return 0;
}