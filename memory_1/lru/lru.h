#include <iostream>
#include <unordered_map>
#include <deque>
template <typename K, typename V>
class LruCache {
private:
    size_t Max_size_;
    size_t Temp_size_;
    std::unordered_map<K, typename std::deque<V>::iterator> mp;
    std::deque<V> Elements_;
    typename std::deque<V>::iterator LRU_;

public:
    LruCache(size_t max_size) : Max_size_(max_size)
    {
        Temp_size_ = 0;
        mp.reserve(Max_size_);
    };

    void Put(const K& key, const V& value)
    {
        V result;
        bool fl = Get(key, &result);
        if (!fl) {
            if(Temp_size_ < Max_size_){
                Elements_.push_back(value);
                ++Temp_size_;
            } else {
                for(auto it1 = mp.begin(); it1 != mp.end();++it1){
                    if(it1->second == Elements_.begin()){
                        mp.erase(it1);
                        break;
                    }
                }
                Elements_.pop_front();
                Elements_.push_back(value);

                /*for(size_t i = 0; i < Max_size_ - 1; ++i) {
                    Elements_[i] = Elements_[i + 1];
                }
                Elements_[Max_size_ - 1] = value;*/
            }
        }else {
            Elements_.erase(mp[key]);
            Elements_.push_back(value);
        }
        mp[key] = Elements_.end() - 1;
    }

    bool Get(const K& key, V* value)
    {
        auto it = mp.find(key);
        if(it == mp.end())
            return false;
        else
        {
            *value = *(it->second);
            Elements_.erase(it->second);
            Elements_.push_back(*it->second);
            mp[key] = Elements_.end() - 1;

            return true;
        }
    }
};