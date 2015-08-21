//===----------------------------------------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#pragma once

//
// count_if is implemented by reduce
//
template<typename InputIt, typename UnaryPredicate,
         utils::EnableIf<utils::isInputIt<InputIt>> = nullptr>
typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p) {
  typedef typename std::iterator_traits<InputIt>::value_type T;

  return reduce(first, last, 0, [&](const T& a, const T& b) {
    return p(b) ? (a + 1) : a;
  });
}

//
// count is implemented by reduce
//
template<typename InputIt, typename T,
         utils::EnableIf<utils::isInputIt<InputIt>> = nullptr>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value) {
  return reduce(first, last, 0, [&](const T& a, const T& b) {
    return (b == value) ? (a + 1) : a;
  });
}


//
// max_element is implemented by reduce
//
template<typename ForwardIt, typename Compare,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare cmp) {
  ForwardIt result = first;
  result = __reduce(first, last, result, [&](const ForwardIt& a, const ForwardIt& b) {
    return cmp(*a, *b) ? b : a;
  });
  return result;
}

//
// max_element is implemented by reduce
//
template<typename ForwardIt,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
ForwardIt max_element(ForwardIt first, ForwardIt last) {
  typedef typename std::iterator_traits<ForwardIt>::value_type T;
  return std::experimental::parallel::max_element(first, last, std::less<T>());
}


//
// min_element is implemented by reduce
//
template<typename ForwardIt, typename Compare,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare cmp) {
  ForwardIt result = first;
  result = __reduce(first, last, result, [&](const ForwardIt& a, const ForwardIt& b) {
    return cmp(*a, *b) ? a : b;
  });
  return result;
}

//
// min_element is implemented by reduce
//
template<typename ForwardIt,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
ForwardIt min_element(ForwardIt first, ForwardIt last) {
  typedef typename std::iterator_traits<ForwardIt>::value_type T;
  return std::experimental::parallel::min_element(first, last, std::less<T>());
}


//
// minmax_element is implemented by reduce
//
template<typename ForwardIt, typename Compare,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last, Compare cmp) {
  return {
    std::experimental::parallel::min_element(first, last, cmp),
    std::experimental::parallel::max_element(first, last, cmp)
  };
}


//
// minmax_element is implemented by reduce
//
template<typename ForwardIt,
         utils::EnableIf<utils::isForwardIt<ForwardIt>> = nullptr>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last) {
  typedef typename std::iterator_traits<ForwardIt>::value_type T;
  return std::experimental::parallel::minmax_element(first, last, std::less<T>());
}


//
// any_of is implemented by transform_reduce
//
template<typename InputIt, typename UnaryPredicate,
         utils::EnableIf<utils::isInputIt<InputIt>> = nullptr>
bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  typedef typename std::iterator_traits<InputIt>::value_type T;

  return transform_reduce(first, last, p, true,
                          [](bool a, bool b) { return a && b; });
}


//
// any_of is implemented by transform_reduce
//
template<typename InputIt, typename UnaryPredicate,
         utils::EnableIf<utils::isInputIt<InputIt>> = nullptr>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  typedef typename std::iterator_traits<InputIt>::value_type T;

  return transform_reduce(first, last, p, false,
                          [](bool a, bool b) { return a || b; });
}


//
// none_of is implemented by transform_reduce
//
template<typename InputIt, typename UnaryPredicate,
         utils::EnableIf<utils::isInputIt<InputIt>> = nullptr>
bool none_of( InputIt first, InputIt last, UnaryPredicate p ) {
  return any_of(first, last, p) == false;
}

