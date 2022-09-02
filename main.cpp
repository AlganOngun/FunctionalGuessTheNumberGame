#include <fplus/fplus.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto write_to_file(const std::string&& path_to_file, const std::string& content_to_write) -> void {
  auto file_handle {std::ofstream(path_to_file)};
  file_handle << content_to_write;
}

auto read_file(const std::string& path_to_file) -> std::string {
  auto file_handle {std::ifstream(path_to_file)};
  auto content {std::string {""}};
  file_handle >> content;

  return content;
}

auto personal_record(int newRecord) -> void {
  write_to_file("gameData.cgd", std::to_string(newRecord));
}

template<typename F, typename container>
auto return_instead_if(F function, const container&& alternativeContainer, const container& cont)
    -> container {
  return ([&]() {
    if (function(cont)) return alternativeContainer;
    else return cont;
  })();
}

auto personal_record() -> int {
  const auto data = read_file("gameData.cgd");
  const auto secureData {
      return_instead_if([](auto cont) { return cont == ""; }, std::string {"9999999"}, data)};
  return std::stoi(secureData);
}

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

        if (guess_count < personal_record()) {
          personal_record(guess_count);
          std::cout << "Congrats you have a new record of " << guess_count << " guessses\n";
        }
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
