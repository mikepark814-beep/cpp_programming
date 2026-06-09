#pragma once

#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

// my_vector<T>
//   내부 저장소는 raw 포인터 (T* data_) + size_ + capacity_ 로 직접 관리한다.
//   메모리 "확보" 와 객체 "생성" 을 std::allocator<T> 로 분리한다.
//
// std::allocator 의 4 가지 기본 동작:
//   - alloc_.allocate(n)        : 생성 없이 n 칸의 raw 메모리만 확보한다.
//   - std::construct_at(p, ...) : p 가 가리키는 raw 자리에 객체를 제자리 생성한다.
//   - std::destroy_n(p, n)      : p 부터 n 개의 살아 있는 객체를 파괴한다.
//   - alloc_.deallocate(p, n)   : raw 메모리를 반납한다 (allocate 와 같은 n).
//
// 예외 처리 정책:
//   - at(i)         : i >= size_ 이면 std::out_of_range 를 throw 한다.
//   - operator[](i) : 범위 검사를 하지 않는다.
//
// push_back vs emplace_back:
//   - push_back(const T&) / push_back(T&&) : 이미 만들어진 T 를 받는다.
//   - emplace_back(Args&&...)              : 가변 인자 + 완벽 전달로
//                                            빈 자리에 T 를 직접 짓는다(construct_at).
template <typename T>
class my_vector {
public:
    // TODO: 기본 생성자
    my_vector() = default;

    // TODO: std::initializer_list<T> 를 받는 생성자 (allocate + construct_at)
    my_vector(std::initializer_list<T> il) {
        if (il.size() > 0) {
            data_ = alloc_.allocate(il.size());
            capacity_ = il.size();
            for (const auto& v : il) {
                std::construct_at(data_ + size_, v);
                ++size_;
            }
        }
    }

    // TODO: 소멸자 — 살아 있는 원소 destroy_n, raw 메모리 deallocate
    ~my_vector() { clear_and_dealloc(); }

    // TODO: 복사 생성자 / 복사 대입 (깊은 복사: allocate + construct_at)
    my_vector(const my_vector& other) {
        if (other.size_ > 0) {
            data_ = alloc_.allocate(other.size_);
            capacity_ = other.size_;
            for (std::size_t i = 0; i < other.size_; ++i)
                std::construct_at(data_ + i, other.data_[i]);
            size_ = other.size_;
        }
    }

    my_vector& operator=(const my_vector& other) {
        if (this == &other) return *this;
        clear_and_dealloc();
        if (other.size_ > 0) {
            data_ = alloc_.allocate(other.size_);
            capacity_ = other.size_;
            for (std::size_t i = 0; i < other.size_; ++i)
                std::construct_at(data_ + i, other.data_[i]);
            size_ = other.size_;
        }
        return *this;
    }

    // TODO: 이동 생성자 / 이동 대입 (noexcept, 포인터 교환)
    my_vector(my_vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    my_vector& operator=(my_vector&& other) noexcept {
        if (this == &other) return *this;
        clear_and_dealloc();
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    // TODO: size(), capacity(), empty()
    [[nodiscard]] std::size_t size()     const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool        empty()    const noexcept { return size_ == 0; }

    // TODO: operator[] — Deducing This, 범위 검사 없음
    template <typename Self>
    [[nodiscard]] decltype(auto) operator[](this Self&& self, std::size_t i) noexcept {
        return std::forward<Self>(self).data_[i];
    }

    // TODO: at() — Deducing This, std::out_of_range throw
    template <typename Self>
    [[nodiscard]] decltype(auto) at(this Self&& self, std::size_t i) {
        if (i >= self.size_) throw std::out_of_range("my_vector::at");
        return std::forward<Self>(self).data_[i];
    }

    // TODO: reserve(std::size_t new_capacity)
    //         새 메모리 allocate → 원소 제자리 이동 생성 → 옛 원소 destroy_n → deallocate
    void reserve(std::size_t new_cap) {
        if (new_cap <= capacity_) return;
        T* new_data = alloc_.allocate(new_cap);
        for (std::size_t i = 0; i < size_; ++i)
            std::construct_at(new_data + i, std::move(data_[i]));
        std::destroy_n(data_, size_);
        if (data_) alloc_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_cap;
    }

    // TODO: push_back(const T&) / push_back(T&&) — construct_at 으로 제자리 생성
    void push_back(const T& value) { emplace_back_impl(value); }
    void push_back(T&& value)      { emplace_back_impl(std::move(value)); }

    // TODO: template <typename... Args>
    //           requires std::constructible_from<T, Args...>
    //       T& emplace_back(Args&&... args);   // construct_at 으로 제자리 생성
    //   참고: 자리가 가득 차 새 버퍼로 옮겨야 할 때는, 새 원소를 옛 버퍼가 아직
    //   살아 있는 동안 새 버퍼에 "먼저" 생성한 뒤 옛 원소를 옮기고 옛 버퍼를
    //   마지막에 해제한다. 그래야 v.push_back(v[0]) 같은 자기참조 인자도 안전하다.
    template <typename... Args>
        requires std::constructible_from<T, Args...>
    T& emplace_back(Args&&... args) {
        return emplace_back_impl(std::forward<Args>(args)...);
    }

    // TODO: begin() / end() — Deducing This, raw 포인터를 반환
    template <typename Self>
    [[nodiscard]] auto begin(this Self&& self) noexcept { return self.data_; }

    template <typename Self>
    [[nodiscard]] auto end(this Self&& self) noexcept { return self.data_ + self.size_; }

private:
    // alloc_ 는 가장 먼저 선언한다 (data_ 초기화보다 먼저 살아 있어야 함).
    std::allocator<T> alloc_{};
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void clear_and_dealloc() {
        std::destroy_n(data_, size_);
        if (data_) alloc_.deallocate(data_, capacity_);
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    template <typename... Args>
    T& emplace_back_impl(Args&&... args) {
        if (size_ < capacity_) {
            std::construct_at(data_ + size_, std::forward<Args>(args)...);
            return data_[size_++];
        }
        // 새 원소를 옛 버퍼가 살아있는 동안 먼저 생성 (v.push_back(v[0]) 안전 처리)
        std::size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = alloc_.allocate(new_cap);
        std::construct_at(new_data + size_, std::forward<Args>(args)...);
        for (std::size_t i = 0; i < size_; ++i)
            std::construct_at(new_data + i, std::move(data_[i]));
        std::destroy_n(data_, size_);
        if (data_) alloc_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_cap;
        return data_[size_++];
    }
};
