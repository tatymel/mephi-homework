#include <iostream>
#include <map>
template <typename K, typename V>
class LruCache {
private:
    size_t Max_size_;
    size_t Temp_size_;
    std::map<K, V> mp;

public:
    LruCache(size_t max_size) : Max_size_(max_size)
    {
        Temp_size_ = 0;
    };

    void Put(const K& key, const V& value)
    {
        if(Temp_size_ < Max_size_)
            mp[key] = value;
    }

    bool Get(const K& key, V* value);
};
