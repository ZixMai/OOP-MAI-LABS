#pragma once

#include <coroutine>
#include <exception>

struct Coroutine {
    struct promise_type {
        bool finished = false;

        Coroutine get_return_object() {
            return Coroutine{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend() { return {}; }

        std::suspend_always final_suspend() noexcept {
            finished = true;
            return {};
        }

        void return_void() {
        }

        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> coro;

    explicit Coroutine(std::coroutine_handle<promise_type> coro) : coro(coro) {
    }

    Coroutine(Coroutine && other) noexcept : coro(other.coro) { other.coro = nullptr; }

    Coroutine(const Coroutine &) = delete;

    Coroutine &operator=(const Coroutine &) = delete;

    bool is_done() const {
        return coro.promise().finished;
    }

    void resume() const {
        if (!is_done()) {
            coro.resume();
        }
    }

    ~Coroutine() {
        if (coro) {
            coro.destroy();
        }
    }
};

