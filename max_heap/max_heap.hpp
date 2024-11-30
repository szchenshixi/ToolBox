#include <algorithm>
#include <queue>
#include <set>

// Template to extract types from std::pair
template <typename T>
struct PairTraits;

// Specialization for std::pair
template <typename T1, typename T2>
struct PairTraits<std::pair<T1, T2>> {
    using FirstType = T1;
    using SecondType = T2;
};

template <typename T>
struct TopKCmp {
    using K = typename PairTraits<T>::FirstType;
    using V = typename PairTraits<T>::SecondType;
    bool operator()(T left, T right) {
        K leftKey = left.first;
        K rightKey = right.first;
        return leftKey < rightKey;
    }
};

template <typename T>
class TopK {
    using K = typename PairTraits<T>::FirstType;
    using V = typename PairTraits<T>::SecondType;

  public:
    TopK(int size)
        : mK(size) {}

    bool emplace(const T&& item) {
        K key = item.first;
        if (!mSeen.insert(key).second) {
            // Skip duplicated items
            return false;
        }
        if (mQueue.size() < mK) {
            mQueue.emplace(item);
            return true;
        }
        if (key < mQueue.top().first) {
            mQueue.pop();
            mQueue.emplace(item);
            return true;
        }
        return false;
    }
    std::vector<T> finalize() {
        std::vector<T> ret;
        ret.reserve(mQueue.size());
        while (!mQueue.empty()) {
            ret.emplace_back(mQueue.top());
            mQueue.pop();
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

  private:
    int mK;
    std::priority_queue<T, std::vector<T>, TopKCmp<T>> mQueue;
    std::set<K> mSeen;
};
