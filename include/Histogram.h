//
// Created by Eric Pfister on 11/10/20.
//

#ifndef IDEAL_GAS_INCLUDE_HISTOGRAM_H_
#define IDEAL_GAS_INCLUDE_HISTOGRAM_H_
#include <vector>
#include <cinder/gl/gl.h>
namespace idealgas {
class Histogram {
 private:
  const double AXIS_LINE_WIDTH = 2.0;
  size_t number_of_bins_;
  double bin_width_;
  double y_axis_max_;
 public:
 private:
  std::vector<double> data_;
  cinder::Rectf dimensions_;
  std::string title_;
  std::string DoubleToString(double num, size_t precision);
  void DrawAxis();
  void DrawData();
 public:
  Histogram(cinder::Rectf dimensions,
            std::string title = "",
            size_t number_of_bins = 0,
            double bin_width = 1,
            double y_axis_max = 0,
            std::vector<double> const &data = std::vector<double>());
  double GetBinWidth() const {
    return bin_width_;
  }
  void SetBinWidth(double bin_width) {
    bin_width_ = bin_width;
  }
  double GetYAxisMax() const {
    return y_axis_max_;
  }
  void SetYAxisMax(double y_axis_max) {
    y_axis_max_ = y_axis_max;
  }
  cinder::Rectf const &GetDimensions() const {
    return dimensions_;
  }
  void SetDimensions(cinder::Rectf const &dimensions) {
    dimensions_ = dimensions;
  }
  std::string const &GetTitle() const {
    return title_;
  }
  void SetTitle(std::string const &title) {
    title_ = title;
  }
  size_t GetNumberOfBins() const {
    return number_of_bins_;
  }
  void SetNumberOfBins(size_t number_of_bins) {
    number_of_bins_ = std::max(1ul, number_of_bins);
  }
  std::vector<double> const &GetData() const {
    return data_;
  }
  void SetData(std::vector<double> const &data) {
    data_ = data;
    if (y_axis_max_ == 0) y_axis_max_ = data.size();
  }
  void Draw();

};
}
#endif //IDEAL_GAS_INCLUDE_HISTOGRAM_H_
