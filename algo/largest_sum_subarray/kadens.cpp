#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#include <functional>
#include <sstream>
#include <numeric>

template <typename T>
struct matrix_t {
        // (rows, columns)
        matrix_t (size_t height, size_t width)
            : _height(height)
            , _width(width)
            , _data(height * width, 0)
            {};

        void init(std::istream &in) {
            std::copy_n( std::istream_iterator<T>(in), _height*_width, std::back_insert_iterator<std::vector<T>>( _data ));
        }

        auto operator[](size_t i) const {
            return std::begin( _data ) + i*_width;
        }

        auto operator[](size_t i)  {
            return std::begin( _data ) + i*_width;
        }

        inline size_t get_height() const {
            return _height;
        }

        inline size_t get_width() const {
            return _width;
        }

    private:
        std::vector<T> _data;
        size_t _height;
        size_t _width;
};



// Implementation of Kadane's algorithm for 1D array. 
// The function returns maximum sum subarray tuple with:
//  - sum
//  - starting index
//  - ending index 

template <typename T>  
auto get_maximal_sub_array(const std::vector<T>& in) {
 
    T global_max  = std::numeric_limits< T >::min();
    T local_max   = 0;
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
  
// Kadane's 2d - matrix
//https://www.geeksforgeeks.org/maximum-sum-rectangle-in-a-2d-matrix-dp-27/
// output tuple:
//              - max_sum
//              - top
//              - left
//              - bottom
//              - right

template <typename T>
auto get_maximal_sub_rectangle(const matrix_t<T>& in) {
    T gm = std::numeric_limits<T>::min();
    size_t i_max_top;
    size_t i_max_left;
    size_t i_max_bottom;
    size_t i_max_right;
    
    std::vector<T> tmp(in.get_height(), 0);

    for (size_t i_left = 0; i_left < in.get_width(); ++i_left){
        std::fill( std::begin(tmp), std::end(tmp), 0);
        for (size_t i_right = i_left; i_right < in.get_width(); ++i_right){
            for (size_t i = 0; i < in.get_height(); i++) {
                std::cout <<"e:"<< in[i_right][i] << "\t"; 
               tmp[i] += in[i_right][i];
            }
            std::cout << std::endl;
            for (auto a: tmp){
                std::cout << a << "\t";
            }

            auto msa = get_maximal_sub_array(tmp);
            auto lm  = std::get<0>(msa);
            std::cout << lm << std::endl;
            if ( gm < lm ) {
                gm = lm;
                i_max_left  = i_left;
                i_max_right = i_right;
                i_max_top   = std::get<1>(msa);
                i_max_bottom  = std::get<2>(msa);
            } 
        }
    }

    return std::make_tuple( gm, i_max_top, i_max_left, i_max_bottom, i_max_right );
}



//main
int main() 
{ 
    std::vector<int32_t> in = {-2, -3, 4, -1, 2, -1, 5, -3}; 
    int32_t max;
    size_t  i_start, i_end;
    std::tie(max, i_start, i_end) = get_maximal_sub_array( in );
 
    std::cout   << "Maximum contiguous sum is: "    << max      << std::endl 
                << "Starting index: "               << i_start  << std::endl 
                << "Ending index: "                 << i_end    << std::endl; 


    matrix_t<int32_t> m(4, 5);
    int32_t M[4][5] = {{1, 2, -1, -4, -20}, 
					    {-8, -3, 4, 2, 1}, 
					    {3, 8, 10, 1, 3}, 
					    {-4, -1, 1, 7, -6} };

    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 5; j++){
            m[i][j] = M[i][j];
        } 
    } 
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 5; j++){
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl; 
    } 

    auto mr = get_maximal_sub_rectangle( m );
    std::cout   << std::endl << "Maximal sub rectangle:" << std::endl
                << "["  << std::get<1>(mr)  << "," << std::get<2>(mr) << "] (Top, Left)" << std::endl
                << "["  << std::get<3>(mr)  << "," << std::get<4>(mr) << "] (Bottom, Right)" << std::endl
                << "Max sum is: " << std::get<0>(mr) << std::endl;


    return 0; 
} 

