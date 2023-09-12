#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class Ideal_cache{
public:
    Ideal_cache(int size_cache) : size_cache(size_cache){}

    void data_put(int key, int index){

        if (data.find(key) == data.end()){
            data[key].first = 1;
        }

        else{
            data[key].first += 1;
            data[key].second.push_back(index);
        }
    }

    int get(int key){
        if (cache_element.find(key) != cache_element.end()){
            return 1;
        }
        return 0;
    }

    void put_in_cache(int key, int element){
        if (size_cache == 0){
            cout << "нулевой размер кэша" << endl;
            return;
        }

        if (cache_element.find(key) != cache_element.end()){
            data[key].first--;
            data[key].second.pop_front();

            if (data[key].second.empty()){
               data.erase(key);
            }
        }


        else if (cache_element.size() < size_cache){

            if (data[key].first == 1){
                data.erase(key);
                return;
            }

            cache_element[key] = element;
            data[key].first--;
            data[key].second.pop_front();

            list_element_cache.push_back(element);
            if (data[key].second.empty()){
               data.erase(key);
            }
        }

        else{
            if (data[key].first == 1){
                data.erase(key);
                return;
            }

            int key_last = 0;
            auto old_elem_it = list_element_cache.begin();

            for (auto elem_it = list_element_cache.begin(); elem_it != list_element_cache.begin(); elem_it++ ){
                if (key_last < *(data[*elem_it].second.end())){
                    key_last = *(data[*elem_it].second.end());
                    old_elem_it = elem_it;
                }
            }

            data[key].first--;
            data[key].second.pop_front();

            cache_element.erase(key_last);
            cache_element[key] = element;

            list_element_cache.erase(old_elem_it);
            list_element_cache.push_back(element);



        }
    }

private:
    int size_cache;
    unordered_map <int, pair<int, list <int>>> data;
    list <int> list_element_cache;
    unordered_map <int, int> cache_element;
};

int main()
{
    int size_cache = 0, quanity_element = 0, kol = 0;
    vector <int> vector_element;
    cin >> size_cache >> quanity_element;
    Ideal_cache cache(size_cache);

    for (int i = 0; i < quanity_element; i++){
         int element;
         cin >> element;
         int key = element;
         int index = i;

         vector_element.push_back(element);
         cache.data_put(key, index);
    }

    for (int i = 0; i < vector_element.size(); i++){
       int key =vector_element[i];
       kol += cache.get(key);
       cache.put_in_cache(key, vector_element[i]);

    }

    cout << kol;

    return 0;
}
