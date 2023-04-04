#ifndef CIRCLE_H
#define CIRCLE_H
#include <algorithm>

//lhs - left hand side
//rhs - right hand side
//t   - road offset

template<class TL, class TR>
constexpr auto circ_add(
    const TL& lhs,
    const TR& rhs,
    const decltype(lhs + rhs) rmin = 0,
    const decltype(lhs + rhs) rmax = 360)
{
    auto c = lhs + rhs;
    auto range = rmax - rmin;
    while (c >= rmax)  c -= range;
    while (c <  rmin)  c += range;
    return c;
}

template<class TL, class TR>
constexpr auto circ_sub(const TL& lhs, const TR& rhs, const decltype(lhs - rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    auto c = lhs - rhs;
    auto range = rmax - rmin;
    while (c >= rmax)  c -= range;
    while (c < rmin)  c += range;
    return c;
}

template<class TL, class TR>
constexpr auto circ_mul(const TL& lhs, const TR& rhs, const decltype(lhs * rhs) rmin = 0, const decltype(lhs * rhs) rmax = 360)
{
    auto c = lhs * rhs;
    auto range = rmax - rmin;
    while (c >= rmax)  c -= range;
    while (c < rmin)  c += range;
    return c;
}

template<class TL, class TR>
constexpr auto circ_div(const TL& lhs, const TR& rhs, const decltype(lhs / rhs) rmin = 0, const decltype(lhs / rhs) rmax = 360)
{
    auto c = lhs / rhs;
    auto range = rmax - rmin;
    while (c >= rmax)  c -= range;
    while (c < rmin)  c += range;
    return c;
}


template<class TL, class TR>
constexpr auto circ_lerp(const double t, const TL& lhs, const TR& rhs, const decltype(lhs - rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    return circ_add(lhs, circ_sub(rhs, lhs, rmin, rmax) * t, rmin, rmax);
}

template<class TL, class TR>
constexpr auto circ_shortdist(const TL& lhs, const TR& rhs, const decltype(lhs-rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    auto a = circ_sub(rhs, lhs, rmin, rmax);
    auto b = circ_sub(lhs, rhs, rmin, rmax);
    return std::min(a, b);
}

template<class TL, class TR>
constexpr auto circ_longdist(const TL& lhs, const TR& rhs, const decltype(lhs - rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    auto a = circ_sub(rhs, lhs, rmin, rmax);
    auto b = circ_sub(lhs, rhs, rmin, rmax);
    return std::max(a, b);
}

template<class TL, class TR>
constexpr auto circ_shortdiff(const TL& lhs, const TR& rhs, const decltype(lhs - rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    auto a = circ_sub(rhs, lhs, rmin, rmax);
    auto b = circ_sub(lhs, rhs, rmin, rmax);
    if (b > a)
        return a;
    else
        return -b;
}

template<class TL, class TR>
constexpr auto circ_shortlerp(const double t, const TL& lhs, const TR& rhs, const decltype(lhs - rhs) rmin = 0, const decltype(lhs - rhs) rmax = 360)
{
    auto a = circ_sub(rhs, lhs, rmin, rmax);
    auto b = circ_sub(lhs, rhs, rmin, rmax);
    if(a < b)
        return circ_add(lhs, a * t, rmin, rmax);
    else
        return circ_sub(lhs, b * t, rmin, rmax);
}


#endif // CIRCLE_H
