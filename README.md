# opencv-adapters

## Overview 

OpenCV's API makes it hard to write modern C++. opencv-adapters helps make that a little bit easier.

## Installation 

Currently opencv-adapters is header-only, so just add the files to your header include paths.

### Dependencies 
opencv-adapters depends on OpenCV being already installed.

## Usage

### RowRange
`RowRange` is an adapter to iterate over two-dimensional `Mat` objects by row. It provides `begin()` and `end()` methods, allows usage anywhere forward iterators are accepted. This is especially useful with the range-based `for` loop, introduced in C++11. Each row is returned as a `Mat` that shares data with the original `Mat`. The helper function `make_RowRange()` is provided to deduce the type when provided with `Mat_<>` instances.

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include "RowRange.hpp"

int main()
{
    // Templated Mat_<> provides the most type safety
    cv::Mat_<float> m1 = cv::Mat_<float>::eye(4, 4);
    
    for (const auto row : cv::make_RowRange(m1))
    {
        // row(0) = 3; <-- this won't compile, since row is const
        std::cout << row << std::endl;
    }

    // But RowRange works just as well with Mat
    cv::Mat m2 = cv::Mat::zeros(3, 3, CV_8UC1);
    for (auto row : cv::RowRange<uchar>(m2))
    {
        row(1) = 255; // <-- not const, so we can modify data
    }
    std::cout << m2 << std::endl; // Prints  [0, 255, 0;
                                  //          0, 255, 0;
                                  //          0, 255, 0]
    
}
```
