#include <thread>
#include <functional>

#ifndef DEBUG
#  define DEBUG 0
#endif

#if DEBUG == 1
#  define DEBUG_PRINT(x) do { puts(x); fflush(stdout); } while (0)
#else
#  define DEBUG_PRINT(x) do { ; } while (0)
#endif

template<typename T>
class stacktor {
private:
    std::thread provider;
    T data_swap;
    T * data = nullptr;
    size_t current_size =  0;
    size_t request      = -1;
    size_t order        = -1;
    bool do_exit = false;

    int lock = 0;

    void bahaha() {
        asm (
            "movq %%rsp, %0;"
                : "=r" (data)
                :
                :
        );

        while (not lock);

        this->god_have_mercy();
    }

    void god_have_mercy() {
        T prayers;
        --lock;

        DEBUG_PRINT("Locking.");
        while (not lock) {
            if (request != -1) {
                data_swap = data[-request];
                request   = -1;
                DEBUG_PRINT("Data request satisfied.");
            }
            if (order != -1) {
                data[-order] = data_swap;
                order        = -1;
                DEBUG_PRINT("Data order satisfied.");
            }
            if (do_exit) {
                return;
            }
        }
        this->god_have_mercy();
    }

public:
    stacktor() : provider(std::bind(&stacktor::bahaha, this)) {
        DEBUG_PRINT("Waiting for data field initialization...");
        while (not data);
        DEBUG_PRINT("Stacktor initialized.");
    }

    //stacktor(const stacktor& other);

    //stacktor(stacktor&& other) noexcept;

    ~stacktor() {
        do_exit = true;
        provider.join();
    }

    //stacktor& operator=(const stacktor& other);

    //stacktor& operator=(stacktor&& other) noexcept;

    void push_back(const T& value) {
        DEBUG_PRINT("Push initiated...");
        lock = 1;
        while (lock);
        this->set(this->current_size, value);
        this->current_size += 1;
    }

    void pop_back() {
        --current_size;
    }

    size_t size() const {
        return this->current_size;
    }

    bool empty() const {
        return (this->size() == 0);
    }

    void clear() {
        current_size = 0;
    }

    T& get(size_t index) {
        DEBUG_PRINT("Request initiated...");

        request = index;
        while (request != -1);
        DEBUG_PRINT("Response recieved.");
        return data_swap;
    }

    void set(size_t index, T value) {
        DEBUG_PRINT("Data order initiated...");

        data_swap = value;
        order     = index;
        while (order != -1);
        DEBUG_PRINT("Data order followed.");
        return;
    }
};
