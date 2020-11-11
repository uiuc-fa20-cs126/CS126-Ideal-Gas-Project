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
  /**
   * How thick the axis lines are
   */
  const double AXIS_LINE_WIDTH = 2.0;
  /**
   * How much to rotate the x-axis data ticks by
   * Allows fitting longer numbers in a smaller space
   */
  const double X_AXIS_TICK_ROTATION_RADIANS = 0.8;
  /**
   * The number of bins on the histogram
   */
  size_t number_of_bins_;
  /**
   * The width of data values each bin holds
   */
  double bin_width_;
  /**
   * The max y-axis value of the histogram
   */
  double y_axis_max_;
 public:
 private:
  /**
   * The data the histogram references
   */
  std::vector<double> data_;
  /**
   * Where the histogram will be rendered in the window
   */
  cinder::Rectf dimensions_;
  /**
   * Title of the histogram, displayed above the graph
   */
  std::string title_;
  /**
   * Converts a double to a string, with a specified precision
   * @param num the double to convert
   * @param precision the number of decimals
   * @return a formatted double string
   */
  std::string DoubleToString(double num, size_t precision);
  /**
   * Helper method to draw a rotated string
   * @param str the string to draw
   * @param pos the position to draw the string at
   * @param radians the rotation of the string, clockwise being positive
   * @param color the color the string should be drawn as
   * @param centered whether or not the string is centered aligned or left aligned
   */
  void DrawRotatedString(std::string const &str,
                         glm::vec2 const &pos,
                         float radians,
                         cinder::ColorA color = cinder::ColorA::black(),
                         bool centered = false);
  /**
   * Draws the axis and their labels
   */
  void DrawAxis();
  /**
   * Draws the bars of the histogram according to the data
   */
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
    if (bin_width < 0) {
      throw std::invalid_argument("bin_width cannot be less than zero");
    }
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
  /**
   * Draws the entire histogram
   */
  void Draw();

};
}
#endif //IDEAL_GAS_INCLUDE_HISTOGRAM_H_
