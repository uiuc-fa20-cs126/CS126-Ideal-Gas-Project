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
  drawStringCentered(title_, dimensions_.getCenter() - vec2(0, height / 2 + 40), ColorA::black());
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
  for (size_t bin = 0; bin <= number_of_bins_; bin++) {
    vec2 text_pos =
        vec2(dimensions_.getLowerLeft().x + bin * width / number_of_bins_, dimensions_.getLowerLeft().y + 10);
    std::string number = DoubleToString(bin * bin_width_, 1);
    if (bin == number_of_bins_) number += "+";
    pushModelMatrix();
    translate(text_pos);
    Rectf tick_mark = Rectf(0, -15, 2, -8);
    drawSolidRect(tick_mark);
    rotate(0.8);
    drawString(number, vec2(0, 0), ColorA::black());
    popModelMatrix();
  }
  drawStringRight("0", dimensions_.getLowerLeft() - vec2(5, 0), ColorA::black());
  drawStringRight(DoubleToString(y_axis_max_, 1), dimensions_.getUpperLeft() - vec2(5, 0), ColorA::black());
  drawStringRight(DoubleToString(y_axis_max_ / 2, 1),
                  dimensions_.getUpperLeft() + vec2(-5, dimensions_.getHeight() / 2),
                  ColorA::black());
  vec2 x_label_pos = dimensions_.getCenter() + vec2(0, height / 2 + 40);
  vec2 y_label_pos = dimensions_.getCenter() - vec2(width / 2 + 40, 0);

  drawStringCentered("Speed", x_label_pos, ColorA::black());
  pushModelMatrix();
  translate(y_label_pos);
  rotate(-1.5708);
  drawStringCentered("Frequency", vec2(0, 0), ColorA::black());
  popModelMatrix();
}
void Histogram::DrawData() {
  double width = dimensions_.getWidth();
  double height = dimensions_.getHeight();
  color(ColorA::hex(0x808080));
  std::map<size_t, size_t> bins_to_counts_;
  for (double d : data_) {
    size_t bin = glm::clamp((size_t) (d / bin_width_), 0ul, number_of_bins_ - 1);
    bins_to_counts_[bin] = (bins_to_counts_.count(bin) != 0) ? bins_to_counts_[bin] + 1 : 1;
  }
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
}
