#include <iostream>

#include <asio.hpp>
#include <asio/experimental/awaitable_operators.hpp>
#include <asio/experimental/deferred.hpp>

#include <chrono>
#include <format>

using namespace asio;
using namespace std::chrono_literals;

template<typename Timer = steady_timer>
awaitable<void> waitFor(typename Timer::duration duration)
{
  Timer t{co_await this_coro::executor, duration};
  co_await t.async_wait(asio::use_awaitable);
}

template <typename Executor>
awaitable<void, Executor> operator<(awaitable<void, Executor> t, steady_timer::duration duration)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, std::move(t), experimental::deferred),
      co_spawn(ex, waitFor(duration), experimental::deferred)
    ).async_wait(
      experimental::wait_for_one(),
      use_awaitable_t<Executor>{}
    );

  if (order[0] == 0)
  {
    if (ex0)
      std::rethrow_exception(ex0);
    else
      co_return;
  }
  else
  {
    throw std::system_error(asio::error::timed_out);
  }
}



int main()
{
  auto start = std::chrono::steady_clock::now();

  io_context io;
  co_spawn( io, waitFor(10s) < 100ms , detached );
  io.run();

  auto duration = std::chrono::steady_clock::now() - start;
  std::cout << std::format("Asynchronous operation took {}", std::chrono::duration_cast<std::chrono::milliseconds>(duration));
}