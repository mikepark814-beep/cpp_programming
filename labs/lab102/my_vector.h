#pragma once

#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>

// TODO: my_vector 를 클래스 템플릿으로 완성하세요.
//
// 요구 사항 요약
//   1) std::initializer_list<T> 를 받는 생성자
//   2) size() — 원소 개수 반환
//   3) operator[] — C++23 Deducing This 로 const/non-const 를 단일 함수
//      템플릿으로 구현 (auto&& operator[](this Self&& self, std::size_t))
//   4) emplace_back — 가변 인자 템플릿(Args&&...) + std::forward 로 완벽 전달
//   5) begin()/end() — 범위 기반 for 지원
template <typename T>
class my_vector {
public:
    my_vector() = default;

    // TODO: data_ 를 초기화하세요.
    my_vector(std::initializer_list<T> values) : data_(values) {};

    // TODO: data_ 의 원소 개수를 반환하세요.
    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    // TODO: Deducing This 로 const/non-const 를 한 번에 구현하세요.
    //   template <typename Self>
    //   auto&& operator[](this Self&& self, std::size_t index) noexcept;
    template <typename Self>
    [[nodiscard]] auto&& operator[](this Self&& self, std::size_t index) noexcept {
        return std::forward<Self>(self).data_[index];
    }

    // TODO: 가변 인자 템플릿과 std::forward 로 완벽 전달하세요.
    template <typename... Args>
        requires std::constructible_from<T, Args...>
    T& emplace_back(Args&&... args) {
        return data_.emplace_back(std::forward<Args>(args)...);
    }

    // TODO: 범위 기반 for 가 동작하도록 data_ 의 반복자를 돌려주세요.
    template <typename Self>
    [[nodiscard]] auto begin(this Self&& self) noexcept {
        return std::forward<Self>(self).data_.begin();
    }

    template <typename Self>
    [[nodiscard]] auto end(this Self&& self) noexcept {
        return std::forward<Self>(self).data_.end();
    }

private:
    std::vector<T> data_;
};
