#include "rational.h"
#include <numeric>

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero();
    } else if (denom < 0) {
        denom = -denom;
        numer = -numer;
    }

    int64_t gcd = std::gcd(numer, denom);
    numer /= gcd;
    denom /= gcd;

    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t lcm_denoms = std::lcm<int64_t>(lhs.denom_, rhs.denom_);
    lhs.Set(lhs.numer_ * (lcm_denoms / lhs.denom_) + rhs.numer_ * (lcm_denoms / rhs.denom_), lcm_denoms);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    Rational a(lhs.numer_, rhs.denom_);
    Rational b(rhs.numer_, lhs.denom_);
    lhs.Set(static_cast<int64_t>(a.numer_) * b.numer_, static_cast<int64_t>(a.denom_) * b.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.Set(ratio.numer_ + ratio.denom_, ratio.denom_);
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.Set(ratio.numer_ - ratio.denom_, ratio.denom_);
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    while (true) {
        std::string str;
        is >> str;
        try {
            std::size_t pos = 0;
            const int numer = std::stoi(str, &pos);
            int denom = 1;
            if (pos != str.size() && str[pos] == '/') {
                str = str.substr(pos + 1);
                denom = std::stoi(str, &pos);
            }
            ratio.Set(numer, denom);
            break;
        } catch (const std::invalid_argument& error) {
        } catch (const std::out_of_range& error) {
        }
    }
    return is;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return {-ratio.GetNumerator(), ratio.GetDenominator()};
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs *= {rhs.GetDenominator(), rhs.GetNumerator()};
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res += rhs;
    return res;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res -= rhs;
    return res;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res *= rhs;
    return res;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    res /= rhs;
    return res;
}

Rational operator++(Rational& ratio, int) {
    Rational tmp = ratio;
    ++ratio;
    return tmp;
}

Rational operator--(Rational& ratio, int) {
    Rational tmp = ratio;
    --ratio;
    return tmp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <
           static_cast<int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() >
           static_cast<int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}