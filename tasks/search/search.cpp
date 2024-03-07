#include "search.h"

#include <algorithm>
#include <cmath>
#include <iostream>

const double EPS = 1e-9;

std::vector<std::string_view> SplitWords(std::string_view str) {
    std::vector<std::string_view> words;
    for (std::size_t index = 0; index < str.size(); ++index) {
        if (std::isalpha(str[index])) {
            std::size_t end_of_word = index + 1;
            for (; end_of_word < str.size() && std::isalpha(str[end_of_word]); ++end_of_word) {
            }

            words.push_back(str.substr(index, end_of_word - index));
            index = end_of_word;
        }
    }
    return words;
}

enum class compare_t { LESS = -1, EQUAL = 0, MORE = +1 };

compare_t CompareCaseInsensitive(const std::string_view& lhs, const std::string_view& rhs) {
    if (lhs.size() != rhs.size()) {
        return lhs.size() < rhs.size() ? compare_t::LESS : compare_t::MORE;
    } else {
        for (std::size_t index = 0; index < lhs.size(); ++index) {
            int lhs_c = std::tolower(lhs[index]);
            int rhs_c = std::tolower(rhs[index]);
            if (lhs_c != rhs_c) {
                return lhs_c < rhs_c ? compare_t::LESS : compare_t::MORE;
            }
        }
        return compare_t::EQUAL;
    }
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> words_in_query = SplitWords(query);
    // remove equal words in query
    {
        std::sort(words_in_query.begin(), words_in_query.end(),
                  [](const std::string_view& lhs, const std::string_view& rhs) {
                      return CompareCaseInsensitive(lhs, rhs) == compare_t::LESS;
                  });
        words_in_query.erase(std::unique(words_in_query.begin(), words_in_query.end(),
                                         [](const std::string_view& lhs, const std::string_view& rhs) {
                                             return CompareCaseInsensitive(lhs, rhs) == compare_t::EQUAL;
                                         }),
                             words_in_query.end());
    }

    // lines[index] = { all line, {words} }
    std::vector<std::pair<std::string_view, std::vector<std::string_view>>> lines;
    for (std::size_t index = 0; index < text.size(); ++index) {
        if (text[index] != '\n') {
            std::size_t end_of_line = index;
            for (; end_of_line < text.size() && text[end_of_line] != '\n'; ++end_of_line) {
            }

            std::string_view line = text.substr(index, end_of_line - index);
            std::vector<std::string_view> words_in_lines = SplitWords(line);
            if (!words_in_lines.empty()) {
                lines.emplace_back(std::move(line), std::move(words_in_lines));
            }
            index = end_of_line;
        }
    }

    // idf[word in query id] = IDF this word
    std::vector<double> idf(words_in_query.size());
    for (std::size_t word_index = 0; word_index < words_in_query.size(); ++word_index) {
        std::size_t count = std::count_if(
            lines.begin(), lines.end(), [&](const std::pair<std::string_view, std::vector<std::string_view>>& line) {
                const std::vector<std::string_view>& line_words = line.second;
                return std::find_if(line_words.begin(), line_words.end(), [&](const std::string_view& word) {
                           return CompareCaseInsensitive(words_in_query[word_index], word) == compare_t::EQUAL;
                       }) != line_words.end();
            });
        if (count != 0) {
            idf[word_index] = std::log(static_cast<double>(lines.size()) / static_cast<double>(count));
        }
    }

    // line_and_tf_idf[index] = {line id, TF-IDF]
    std::vector<std::pair<std::size_t, double>> line_and_tf_idf(lines.size());
    for (std::size_t line_index = 0; line_index < lines.size(); ++line_index) {
        double tf_idf = 0;
        for (std::size_t word_index = 0; word_index < words_in_query.size(); ++word_index) {
            std::size_t count = std::count_if(
                lines[line_index].second.begin(), lines[line_index].second.end(), [&](const std::string_view& word) {
                    return CompareCaseInsensitive(words_in_query[word_index], word) == compare_t::EQUAL;
                });
            tf_idf +=
                static_cast<double>(count) / static_cast<double>(lines[line_index].second.size()) * idf[word_index];
        }
        line_and_tf_idf[line_index] = {line_index, tf_idf};
    }

    std::sort(line_and_tf_idf.begin(), line_and_tf_idf.end(),
              [](const std::pair<std::size_t, double>& lhs, const std::pair<std::size_t, double>& rhs) {
                  if (std::abs(lhs.second - rhs.second) > EPS) {
                      return lhs.second > rhs.second;
                  } else {
                      return lhs.first < rhs.first;
                  }
              });

    std::vector<std::string_view> result;
    for (const auto& [line_index, tf_idf] : line_and_tf_idf) {
        if (result.size() == results_count || tf_idf <= EPS) {
            break;
        }
        result.push_back(lines[line_index].first);
    }

    return result;
}
