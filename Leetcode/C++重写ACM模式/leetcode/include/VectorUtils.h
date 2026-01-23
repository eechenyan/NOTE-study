//Vector.h
#pragma once
#include<iostream>
#include<vector>

/**
 * 向量向量工具类，提供int类型的数字向量打印功能
 */

class VectorUtils {
public:
    /**
     * 打印一维向量（std::vector<int>）
     * @param OneNums 待打印的一维向量
     * 输出格式：以空格分隔元素，首尾加方括号（如 [1 2 3]）
     */
    static void PrintOneNums(const std::vector<int>& OneNums);

    /**
     * 打印二维向量（std::vector<std::vector<int>>）
     * @param TwoNums 待打印的二维向量
     * 输出格式：每层向量单独打印，首尾加方括号，内层向量格式同一维（如 [[1 2], [3 4]]）
     */
    static void PrintTwoNums(const std::vector<std::vector<int>>& TwoNums);
};
