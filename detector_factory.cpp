#pragma once

#include <opencv2/core/core.hpp>

class Detector{
public:
    Detector(){};
    virtual int count(cv::Mat &image) = 0;
    virtual void draw() = 0;
};