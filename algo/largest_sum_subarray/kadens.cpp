#include <iostream> 
#include <vector>
#include <tuple>
#include <limits> 
  
auto get_max_sub_array(const std::vector<int32_t>& in) {
 
    int32_t global_max  = std::numeric_limits< int32_t >::min();
    int32_t local_max   = 0;
    size_t  i_start     = 0;
    size_t  i_end       = 0;
    size_t  i_local_s   = 0; 
  
    for (size_t i = 0; i < in.size(); i++) {

        local_max += in[i]; 
  
        if ( global_max < local_max ) { 
            global_max = local_max; 
            i_start = i_local_s; 
            i_end   = i; 
        } 
  
        if ( local_max < 0 ) { 
            local_max = 0; 
            i_local_s = i + 1; 
        } 
    }
    
    return std::make_tuple( global_max, i_start, i_end );
} 
  
//main
int main() 
{ 
    std::vector<int32_t> in = {-2, -3, 4, -1, 2, -1, 5, -3}; 
    int32_t max;
    size_t  i_start, i_end;
    std::tie(max, i_start, i_end) = get_max_sub_array( in );
 
    std::cout   << "Maximum contiguous sum is: "    << max      << std::endl 
                << "Starting index: "               << i_start  << std::endl 
                << "Ending index: "                 << i_end    << std::endl; 
    return 0; 
} 

