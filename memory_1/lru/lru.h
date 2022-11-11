#include <iostream>
#include <unordered_map>
#include <list>
template <typename K, typename V>
class LruCache {
private:
    size_t Max_size_;
    size_t Temp_size_;
    std::unordered_map<K, typename std::list<V>::iterator> mp;
    std::list<V> Elements_;
public:
    LruCache(size_t max_size) : Max_size_(max_size)
    {
        Temp_size_ = 0;
    };

    void Put(const K& key, const V& value)
    {
        if (mp.find(key) == mp.end()) {
            if(Temp_size_ < Max_size_){
                ++Temp_size_;
            } else {
                for (auto it = mp.rbegin(); it != mp.rend(); --it) {
                    if (it->second == --Elements_.end()) {
                        mp.erase(it);
                        break;
                    }
                }
                Elements_.pop_back();
            }
        }else {
            Elements_.erase(mp[key]);
        }
        Elements_.push_front(value);
        mp[key] = Elements_.begin();
    }

    bool Get(const K& key, V* value)
    {
        auto it = mp.find(key);
        if(it == mp.end())
            return false;
        else
        {
            *value = *(it->second);
            Elements_.push_front(*it->second);
            Elements_.erase(it->second);
            mp[key] = Elements_.begin();
            return true;
        }
    }
};