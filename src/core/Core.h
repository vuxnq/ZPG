#pragma once
#include <memory>

template<typename T>
using ref = std::shared_ptr<T>;

template<typename T>
ref<T> make_ref(T* ptr) {
    return std::shared_ptr<T>(ptr);
}

template<typename T, typename ...Args>
ref<T> make_ref(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
