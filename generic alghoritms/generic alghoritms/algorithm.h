#ifndef __ALGO__
#define __ALGO__

#include<string>
template<class Container, typename T>
void deleteByVal(Container &c, T val){
   for(Container::iterator i = c.begin(); i != c.end(); i++)
      if(*i == val){
         c.erase(i);
         return;
      } 
}

template<class Container, typename T>
typename Container::iterator getIterByVal(Container &c, T val){
   Container::iterator i = c.begin();
   for(; i != c.end(); i++)
      if(*i == val)
         return i;
   return i;
}

template<class Container, typename T>
T min(Container &c){
   if(c.size() == 0)
      return NULL;

   T min = *c.begin();
   for(Container::iterator i = c.begin(); i != c.end(); i++)
      if(min > *i)
        min = *i;         

   return min;
}

template<class Container, typename T>
T max(Container &c){
   if(c.size() == 0)
      return NULL;

   T max = *c.begin();
   for(Container::iterator i = c.begin(); i != c.end(); i++)
      if(max < *i)
         max = *i;

   return max;
}

template<class Container, typename T>
void turn(Container &c){
   Container::iterator i = c.begin(), j = --c.end();
   for(int count = c.size() / 2; count > 0; count--, i++, j--){
      T x = *i;
      *i = *j;
      *j = x;
   }
}

template<class Container, typename T>
void sort(Container &c, bool f(T, T)){
   for(Container::iterator i = c.begin(); i != c.end(); i++)
      for(Container::iterator j = c.begin(); j != c.end(); j++)
         if(f(*i, *j)){
            T x = *i;
            *i = *j;
            *j = x;
         }
}

template<class Container, typename T>
void insertRandVal(Container &c, size_t size, T fval()){
   for(size_t i = 0; i < size; i++){
      T x = fval();
      c.push_back(x);
   }
}

template<class Container, typename K, typename T>
void insertRandVal(Container &c, size_t size, T fval(), K fkey()){
   for(size_t i = 0; i < size; i++){
      T x = fval();
      K k = fkey();
      c.insert(k, x);
   }
}

#endif