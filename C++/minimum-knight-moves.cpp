// Time:  O(1)
// Space: O(1)

class Solution {
public:
    template <typename T>
    struct PairHash {
        size_t operator()(const pair<T, T>& p) const {
            size_t seed = 0;
            seed ^= std::hash<T>{}(p.first)  + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= std::hash<T>{}(p.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };

    int minKnightMoves(int x, int y) {
        // we can observe from:
        // [0]
        // [3, 2]
        // [2, 1, 4]
        // [3, 2, 3, 2]
        // [2, 3, 2, 3, 4]
        // [3, 4, 3, 4, 3, 4]
        // [4, 3, 4, 3, 4, 5, 4]
        // [5, 4, 5, 4, 5, 4, 5, 6]
        // [4, 5, 4, 5, 4, 5, 6, 5, 6]
        // [5, 6, 5, 6, 5, 6, 5, 6, 7, 6]
        // [6, 5, 6, 5, 6, 5, 6, 7, 6, 7, 8]
        // [7, 6, 7, 6, 7, 6, 7, 6, 7, 8, 7, 8]
        // [6, 7, 6, 7, 6, 7, 6, 7, 8, 7, 8, 9, 8]
        // [7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 9, 8, 9, 10]
        // [8, 7, 8, 7, 8, 7, 8, 7, 8, 9, 8, 9, 10, 9, 10]
        // [9, 8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 10, 9, 10, 11, 10]

        x = abs(x), y = abs(y);
        if (x < y) {
            swap(x, y);
        }
        unordered_map<pair<int, int>, int, PairHash<int>> lookup =
            {{{0, 0}, 0}, {{1, 0}, 3}, {{2, 2}, 4}};  // special cases
        if (lookup.count({x, y})) {
            return lookup[{x, y}];
        }
        const auto& delta = x - y;
        if (y > delta) {  // if 2y > x, every period 3 of y with same delta is increased by 2
            return delta + 2 * ((y - delta - 1) / 3 + 1);
        }
        // if 2y <= x, every period 4 of y with same delta is increased by 2
        return delta - 2 * ((delta - y) / 4);
    }
};

// Time:  O(n^2)
// Space: O(n^2)
class Solution2 {
public:
    template <typename T>
    struct PairHash {
        size_t operator()(const pair<T, T>& p) const {
            size_t seed = 0;
            seed ^= std::hash<T>{}(p.first)  + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= std::hash<T>{}(p.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };

    int minKnightMoves(int x, int y) {
        unordered_map<pair<int, int>, int, PairHash<int>> lookup =
            {{{0, 0}, 0}, {{1, 1}, 2}, {{1, 0}, 3}};  // special cases
        return dp(x, y, &lookup);
    }

private:
    int dp(int x, int y,
           unordered_map<pair<int, int>, int, PairHash<int>> *lookup) {
        x = abs(x), y = abs(y);
        if (x < y) {
            swap(x, y);
        }
        if (!lookup->count({x, y})) {
            (*lookup)[{x, y}] = min(dp(x - 1, y - 2, lookup),
                                    dp(x - 2, y - 1, lookup)) + 1;
        }
        return (*lookup)[{x, y}];
    }
};
