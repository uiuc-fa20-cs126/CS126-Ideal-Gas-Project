//
// Created by Eric Pfister on 11/10/20.
//
#include <Histogram.h>
#include <cmath>
#include <map>
using namespace ci;
using namespace gl;
namespace idealgas {
Histogram::Histogram(cinder::Rectf dimensions,
                     std::string title,
                     size_t number_of_bins,
                     double bin_width,
                     double y_axis_max,
                     const std::vector<double> &data) {
  y_axis_max_ = y_axis_max == 0 ? data.size() : y_axis_max;
  title_ = title;
  dimensions_ = dimensions;
  if (number_of_bins == 0) {
    number_of_bins_ = std::max(1ul, (size_t) std::ceil(std::sqrt(data.size())));
  } else {
    number_of_bins_ = number_of_bins;
  }

  data_ = data;
  bin_width_ = bin_width;
}
void Histogram::DrawAxis() {
  color(ColorA::black());
  double width = dimensions_.getWidth();
  double height = dimensions_.getHeight();
  // Draw the title of the graph
  drawStringCentered(title_, dimensions_.getCenter() - vec2(0, height / 2 + 40), ColorA::black());
  // Create and draw the x and y axis with a desired thickness
  Rectf x_axis = Rectf(dimensions_.getLowerLeft().x,
                       dimensions_.getLowerLeft().y + AXIS_LINE_WIDTH,
                       dimensions_.getLowerRight().x,
                       dimensions_.getLowerRight().y);
  Rectf y_axis = Rectf(dimensions_.getLowerLeft().x,
                       dimensions_.getLowerLeft().y,
                       dimensions_.getUpperLeft().x + AXIS_LINE_WIDTH,
                       dimensions_.getUpperLeft().y);
  drawSolidRect(x_axis);
  drawSolidRect(y_axis);

  // Draw the x-axis bins
  for (size_t bin = 0; bin <= number_of_bins_; bin++) {
    vec2 text_pos =
        vec2(dimensions_.getLowerLeft().x + bin * width / number_of_bins_, dimensions_.getLowerLeft().y + 10);
    std::string number = DoubleToString(bin * bin_width_, 1);
    // The last bin value gets a + on the end of it to indicate any data over this bin's width will go here
    if (bin == number_of_bins_) number += "+";
    DrawRotatedString(number, text_pos, X_AXIS_TICK_ROTATION_RADIANS);
  }

  // Draw the y-axis ticks
  drawStringRight("0", dimensions_.getLowerLeft() - vec2(5, 0), ColorA::black());
  drawStringRight(DoubleToString(y_axis_max_, 1), dimensions_.getUpperLeft() - vec2(5, 0), ColorA::black());
  drawStringRight(DoubleToString(y_axis_max_ / 2, 1),
                  dimensions_.getUpperLeft() + vec2(-5, dimensions_.getHeight() / 2),
                  ColorA::black());

  // Draw the axis labels
  vec2 x_label_pos = dimensions_.getCenter() + vec2(0, height / 2 + 40);
  vec2 y_label_pos = dimensions_.getCenter() - vec2(width / 2 + 40, 0);
  drawStringCentered("Speed", x_label_pos, ColorA::black());
  DrawRotatedString("Frequency", y_label_pos, -1.5708, ColorA::black(), true);
}
void Histogram::DrawData() {
  // Gray color
  color(ColorA::hex(0x808080));
  double width = dimensions_.getWidth();
  double height = dimensions_.getHeight();
  // Create a map to store the bin index, and the count of data points that falls within that bins range
  std::map<size_t, size_t> bins_to_counts_;
  for (double d : data_) {
    // Any data greater than the histograms range goes into the last bin
    size_t bin = glm::clamp((size_t) (d / bin_width_), 0ul, number_of_bins_ - 1);
    bins_to_counts_[bin] = (bins_to_counts_.count(bin) != 0) ? bins_to_counts_[bin] + 1 : 1;
  }

  // Draw the bins
  for (size_t bin = 0; bin < number_of_bins_; bin++) {
    size_t frequency = (bins_to_counts_.count(bin) != 0) ? bins_to_counts_[bin] : 0;
    vec2 start_pos = vec2(dimensions_.getLowerLeft().x + bin * width / number_of_bins_, dimensions_.getLowerLeft().y);
    vec2 end_pos = vec2(dimensions_.getLowerLeft().x + (bin + 1) * width / number_of_bins_,
                        dimensions_.getLowerLeft().y - frequency * height / y_axis_max_);
    gl::drawSolidRect(Rectf(start_pos, end_pos));
  }
}
void Histogram::Draw() {
  DrawData();
  DrawAxis();
}

std::string Histogram::DoubleToString(double num, size_t precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << num;
  return stream.str();
}

void Histogram::DrawRotatedString(std::string const &str,
                                  vec2 const &pos,
                                  float radians,
                                  cinder::ColorA color,
                                  bool centered) {
  pushModelMatrix();
  translate(pos);
  rotate(radians);
  if (centered) {
    drawStringCentered(str, vec2(0, 0), color);
  } else {
    drawString(str, vec2(0, 0), color);
  }
  popModelMatrix();
}
}
