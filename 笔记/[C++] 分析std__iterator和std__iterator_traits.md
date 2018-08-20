## std::iterator和std::iterator_traits
------------------------------------------------
### std::iterator  
```std::iterator```是一个模板类，其声明为：  
```
template< 
    class Category,
    class T,
    class Distance = std::ptrdiff_t,
    class Pointer = T*,
    class Reference = T& 
> struct iterator;
```  
**std :: iterator是为简化迭代器所需类型的定义而提供的基类。**
也就是说当我们写一个模板类时，需要定义自己的迭代器iterator，那么我们可以将std::iterator作为自定义迭代器的基类。    

```std::iterator```的模板参数：   

-   Category: 类型为iterator_category ,迭代器的种类。迭代器种类共有5类，参见```c++ primer P365```。分别是  
```输入(input_iterator)```     
```输出(output_iterator)```   
```前向(forward_iterator)```   
```双向(bidirectional_iterator)```    
```随机访问(random_access_iterator)```。  
而表示这些迭代器类型的参数分别用  ```input_iterator_tag```    
```output_iterator_tag```     
```forward_iterator_tag```        
```bidirectional_iterator_tag```     
```random_access_iterator_tag```.
- T :类型为value_type, 可以通过解除引用迭代器获得的值的类型。 对于输出迭代器，此类型应为void。   
- Distance: 类型为difference_type, 一种可用于标识迭代器之间距离的类型。即两个迭代器相减(若支持的话)的结果类型。
- Pointer: 类型为pointer,定义指向迭代类型的指针（T）。即指向T类型的指针。
- Reference: 类型为reference,定义迭代类型的引用（T）。即T的引用类型。  

具体例子：
```
#include <iostream>
#include <algorithm>
 
template<long FROM, long TO>
class Range {
public:
    // member typedefs provided through inheriting from std::iterator
    class iterator: public std::iterator<
                        std::input_iterator_tag,   // iterator_category
                        long,                      // value_type
                        long,                      // difference_type
                        const long*,               // pointer
                        long                       // reference
                                      >{
        long num = FROM;
    public:
        explicit iterator(long _num = 0) : num(_num) {}
        iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return num == other.num;}
        bool operator!=(iterator other) const {return !(*this == other);}
        reference operator*() const {return num;}
    };
    iterator begin() {return iterator(FROM);}
    iterator end() {return iterator(TO >= FROM? TO+1 : TO-1);}
};
 
int main() {
    // std::find requires a input iterator
    auto range = Range<15, 25>();
    auto itr = std::find(range.begin(), range.end(), 18);
    std::cout << *itr << '\n'; // 18
 
    // Range::iterator also satisfies range-based for requirements
    for(long l : Range<3, 5>()) {
        std::cout << l << ' '; // 3 4 5
    }
    std::cout << '\n';
}
```  
Output: 
```
18
3 4 5
```  
 
### std::iterator_traits
```std::iterator_traits```同样是一个模板类。 
**```std :: iterator_traits```是类型```trait```类，它为```Iterator```类型的属性提供统一的接口。 这使得仅在迭代器方面实现算法成为可能。**  
也就是说可以用它访问```iterator```类的一些属性。  
举个例子比如```BidirIt```是一个```iterator```类，我们可以访问它的一些属性。  
```
typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);  
typename std::iterator_traits<BidirIt>::value_type tmp = *first;	
```  
此处注意```typename```不可少，这表示我们是访问的这个类模板的组成参数，而非是它的static成员。