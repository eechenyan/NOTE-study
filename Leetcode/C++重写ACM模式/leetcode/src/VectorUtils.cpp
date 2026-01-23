#include<iostream>
#include<vector>
#include "VectorUtils.h"

void VectorUtils::PrintOneNums(const std::vector<int>& OneNums) {
    for(int i{0};i<OneNums.size();i++) {
        std::cout<<OneNums[i]<<" ";
    }
    std::cout<<std::endl;
}

void VectorUtils::PrintTwoNums(const std::vector<std::vector<int>>& TwoNums) {
    int row = TwoNums.size();
    for(int i{0};i<row;i++) {
        int col = TwoNums[i].size();
        for(int j{0};j<col;j++) {
            std::cout<<TwoNums[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}