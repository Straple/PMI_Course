#include "my_filter.hpp"
#include "gaussian_blur_filter.hpp"

#include <cmath>
#include <queue>
#include <tuple>
#include <set>

MyFilterException::MyFilterException(const std::string& message) : FilterException("My filter exception: " + message) {
}

MyFilter::MyFilter(double blur_sigma, double max_dist, double max_diff)
    : blur_sigma_(blur_sigma), max_dist_(max_dist), max_diff_(max_diff) {
}

void MyFilter::operator()(Image& image) {

    GaussianBlurFilter blur_filter(blur_sigma_);
    blur_filter(image);

    std::vector<std::vector<bool>> visited(image.Height(), std::vector<bool>(image.Width()));

    std::vector<std::vector<double>> dist(image.Height(),
                                          std::vector<double>(image.Width(), std::numeric_limits<double>::infinity()));

    static const std::vector<std::pair<int, int>> STEPS = {
        {0, +1}, {0, -1},

        {+1, 0}, {+1, +1}, {+1, -1},

        {-1, 0}, {-1, +1}, {-1, -1},
    };

    auto is_available_pixel = [&](int row, int column) {
        return 0 <= row && row < static_cast<int>(image.Height()) && 0 <= column &&
               column < static_cast<int>(image.Width());
    };

    auto pixels_traversal = [&](int start_row, int start_column) {
        std::vector<std::pair<int, int>> visited_pixels;

        std::set<std::tuple<double, int, int>> queue;
        queue.insert({0, start_row, start_column});
        dist[start_row][start_column] = 0;

        RGB min_color = image(start_row, start_column);
        RGB max_color = image(start_row, start_column);

        auto update_colors_metric = [&](RGB color) {
            min_color.red = std::min(min_color.red, color.red);
            min_color.green = std::min(min_color.green, color.green);
            min_color.blue = std::min(min_color.blue, color.blue);

            max_color.red = std::max(max_color.red, color.red);
            max_color.green = std::max(max_color.green, color.green);
            max_color.blue = std::max(max_color.blue, color.blue);
        };

        auto calc_metric = [&](RGB color) {
            auto calc = [&](double x, double y, double z) { return (x - y) * (x - y) + (x - z) * (x - z); };
            double metric_red = calc(color.red, min_color.red, max_color.red);
            double metric_green = calc(color.green, min_color.green, max_color.green);
            double metric_blue = calc(color.blue, min_color.blue, max_color.blue);
            return metric_red + metric_green + metric_blue;
        };

        while (!queue.empty()) {
            auto [_, row, column] = *queue.begin();
            queue.erase(queue.begin());

            if (visited[row][column]) {
                throw MyFilterException("internal error: attempting to visit a pixel twice");
            }

            visited[row][column] = true;
            visited_pixels.emplace_back(row, column);
            update_colors_metric(image(row, column));

            for (auto [step_row, step_column] : STEPS) {
                int to_row = row + step_row;
                int to_column = column + step_column;
                if (is_available_pixel(to_row, to_column) && !visited[to_row][to_column]) {

                    double metric = calc_metric(image(to_row, to_column));
                    double cur_dist = dist[row][column] + metric;

                    if (cur_dist < max_dist_ && metric < max_diff_ && cur_dist < dist[to_row][to_column]) {
                        queue.erase({dist[to_row][to_column], to_row, to_column});
                        dist[to_row][to_column] = cur_dist;
                        queue.insert({cur_dist, to_row, to_column});
                    }
                }
            }
        }

        if (visited_pixels.empty()) {
            throw MyFilterException("internal error: visited pixels are empty");
        }

        return visited_pixels;
    };

    auto paint = [&](int start_row, int start_column) {
        std::vector<std::pair<int, int>> visited_pixels = pixels_traversal(start_row, start_column);

        RGB sum_color;
        for (auto [row, column] : visited_pixels) {
            sum_color += image(row, column);
        }

        RGB average_color = sum_color * (1 / static_cast<double>(visited_pixels.size()));
        average_color.Normalize();
        for (auto [row, column] : visited_pixels) {
            image(row, column) = average_color;
        }
    };

    // Очень важно стартовать из правильного места,
    // поэтому возьмем все пиксели. Отсортируем их по нужной метрике.
    // И будем перебирать их в таком порядке
    // хотя метрика говно :_)

    // (metric, row, column)
    std::vector<std::tuple<double, int, int>> pixels;

    auto vector_len = [&](double x, double y, double z) { return sqrt(x * x + y * y + z * z); };

    for (uint32_t row = 0; row < image.Height(); row++) {
        for (uint32_t column = 0; column < image.Width(); column++) {
            RGB color = image(static_cast<int>(row), static_cast<int>(column));
            double metric = vector_len(color.red, color.green, color.blue);
            pixels.push_back({metric, row, column});
        }
    }
    std::sort(pixels.begin(), pixels.end());

    for (auto [metric, row, column] : pixels) {
        if (!visited[row][column]) {
            paint(static_cast<int>(row), static_cast<int>(column));
        }
    }
}
