#include <fplus/fplus.hpp>
#include <iostream>
#include <string>
#include <vector>

template<typename T> auto ask_for_value_from_cin(const std::string& message) {
  T x;
  std::cout << message;
  std::cin >> x;
  return x;
}

enum game_state { PLAYER_VICTORY, HIGHER, LOWER };

auto random_number_in_range(int min, int max) {
  const auto list = fplus::numbers(min, max);

  return fplus::random_element(std::random_device()(), list);
}

auto result_the_game(int random_number, int player_guess) -> game_state {
  return [&]() {
    if (random_number == player_guess) return PLAYER_VICTORY;
    else if (random_number > player_guess) return HIGHER;
    else return LOWER;
  }();
}

auto guessing_game(int random_number) -> void {
  auto guess {[random_number](int guess_count, auto&& guess) -> void {
    const auto player_guess {ask_for_value_from_cin<int>("Guess: ")};

    const auto game_result {result_the_game(random_number, player_guess)};

    switch (game_result) {
      case PLAYER_VICTORY:
        std::cout << "You win\n";
        std::cout << "You Guessed the number in only " << guess_count << " guesses\n";
        break;
      case HIGHER:
        std::cout << "My number is higher\n";
        guess(guess_count + 1, guess);
        break;
      case LOWER:
        std::cout << "My number is lower\n";
        guess(guess_count + 1, guess);
        break;
    }
  }};

  guess(1, guess);
}

auto run_game() -> void {
  system("clear");

  std::cout << "Guess the number between 1 and 100\n";

  const auto random_number {random_number_in_range(0, 101)};

  guessing_game(random_number);

  const auto play_again {ask_for_value_from_cin<char>("Wanna play again? y/n: ")};

  switch (play_again) {
    case 'y': run_game(); break;
    case 'n': std::cout << "Bye\n"; break;
  }
}

int main() {
  run_game();
}
