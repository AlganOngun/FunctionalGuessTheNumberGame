#include <fplus/fplus.hpp>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template<typename T> auto ask_for_value_from_cin(const std::string& message) {
  T x;
  std::cout << message;
  std::cin >> x;
  return x;
}

auto random_number_in_range(int min, int max) {
  const auto list = fplus::numbers(min, max);

  return fplus::random_element(std::random_device()(), list);
}

auto guessingGame(int random_number) -> void {
  auto guess {[random_number](int guessCount, auto&& guess) -> void {
    const auto playerGuess {ask_for_value_from_cin<int>("Guess: ")};

    if (random_number == playerGuess) {
      std::cout << "You win\n";
      std::cout << "You Guessed the number in only " << guessCount << " guesses\n";
      return;
    } else if (random_number > playerGuess) std::cout << "My number is higher\n";
    else if (random_number < playerGuess) std::cout << "My number is lower\n";

    guess(guessCount + 1, guess);
  }};
  guess(1, guess);
}

auto gameFunc() -> void {
  system("clear");

  std::cout << "Guess the number between 1 and 100\n";

  const auto random_number {random_number_in_range(0, 101)};

  guessingGame(random_number);

  const auto play_again {ask_for_value_from_cin<std::string>("Wanna play again? y/n: ")};

  if (play_again == "y") gameFunc();
  else if (play_again == "n") std::cout << "Bye\n";
}

int main() {
  gameFunc();
}
