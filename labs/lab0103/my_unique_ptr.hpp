#pragma once

template <typename T>
class my_unique_ptr {
public:
    my_unique_ptr() = default;

    explicit my_unique_ptr(T* ptr) {
        // TODO: ptr을 이 객체가 소유하도록 저장하세요.
        ptr_ = ptr; 
    }

    ~my_unique_ptr() {
        // TODO: 소유 중인 객체가 있다면 delete로 해제하세요.
        if (ptr_ != nullptr) {
            delete ptr_;
        }
    }

    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    my_unique_ptr(my_unique_ptr&& other) noexcept {
        // TODO: other의 소유권을 가져오고, other는 nullptr 상태로 만드세요.
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        // TODO: 기존 소유 객체를 해제한 뒤 other의 소유권을 가져오세요.
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;

        return *this;
    }

    T* get() const {
        // TODO: 소유 중인 원시 포인터를 반환하세요.
        return ptr_;
    }

    T& operator*() const {
        // TODO: 포인터가 가리키는 객체를 참조로 반환하세요.
        return *ptr_;
    }

    T* operator->() const {
        // TODO: 멤버 접근을 위해 원시 포인터를 반환하세요.
        return ptr_;
    }

    explicit operator bool() const {
        // TODO: nullptr이 아니면 true를 반환하세요.
        if (ptr_ != nullptr) {
            return true;
        }
        return false;
    }

private:
    T* ptr_ = nullptr;
};
