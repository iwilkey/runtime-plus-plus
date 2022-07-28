#ifndef RUNTIME_SRC_UTILS_UTILITIES_H_
#define RUNTIME_SRC_UTILS_UTILITIES_H_

#include <iostream>
#include <vector>
using namespace std;
 
class RuntimeUtilities {
    public: 
    
        RuntimeUtilities();
        ~RuntimeUtilities();

        template <typename T>
        long long int vectorContains(vector<T> & list, T object) {
            for(long long int i = 0; i < list.size(); i++)
            if(list[i] == object)
                return i;
            return -1;
        }

        template <typename T>
        bool vectorErase(vector<T> & list, T object) {
            long long int i = vectorContains(list, object);
            if(i == -1) return false;
            list.erase(list.begin() + i);
            return true;
        }

    private:
};

#endif