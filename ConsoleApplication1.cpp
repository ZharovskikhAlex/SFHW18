#include <iostream>
#include "User.h"
#include "Message.h"
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

void demo_perms(fs::perms p)
{
	std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
		<< '\n';
}

int main()
{
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	if (!user_file)
		// Для создания файла используем параметр ios::trunc
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);

	fs::permissions("users.txt", fs::perms::group_read | fs::perms::group_write | fs::perms::others_read | fs::perms::others_write, fs::perm_options::remove);

	std::cout << "file 'users.txt' permissions: ";
	demo_perms(fs::status("users.txt").permissions());

	if (user_file) {
		User user1("alex", "qwerty", "12345");

		// Запишем данные в файл
		user_file << user1 << std::endl;

		// Чтобы считать данные из файла для первого вользователя, надо установить позицию для чтения в начало файла
		user_file.seekg(0, std::ios_base::beg);

		// Считываем данные из файла
		user_file >> user1;
		std::cout << user1 << std::endl;

		user_file.clear();
		user_file.seekg(0, std::ios_base::end);
		user_file.seekp(0, std::ios_base::end);

		User user2("anya", "qwerty1", "123456");

		// Запишем данные в файл
		user_file << user2 << std::endl;

		// Устанавливаем позицию на чтение для следующего пользователя в начало последней строки (размер строки фиксирован и равен 53)
		user_file.clear();
		user_file.seekg(-54, std::ios_base::cur);

		// Считываем данные из файла
		user_file >> user2;
		std::cout << user2 << std::endl;
	}
	else
	{
		std::cout << "Could not open file users.txt!" << std::endl;
		return 0;
	}

	std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
	if (!message_file)
		// Для создания файла используем параметр ios::trunc
		message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);

	fs::permissions("messages.txt", fs::perms::group_read | fs::perms::group_write | fs::perms::others_read | fs::perms::others_write, fs::perm_options::remove);

	std::cout << "file 'messages.txt' permissions: ";
	demo_perms(fs::status("messages.txt").permissions());

	if (message_file) {
		Message message1("alex", "anya", "Hi anya, how are you doing?");

		// Запишем данные в файл
		message_file << message1 << std::endl;

		// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
		message_file.seekg(0, std::ios_base::beg);

		// Считываем данные из файла
		message_file >> message1;
		std::cout << message1 << std::endl;

		message_file.clear();
		message_file.seekg(0, std::ios_base::end);
		message_file.seekp(0, std::ios_base::end);

		Message message2("anya", "alex", "Hey alex, i am doing well and how are you?");

		// Запишем данные в файл
		message_file << message2 << std::endl;

		message_file.clear();
		message_file.seekg(-47 - message2.getText().size(), std::ios_base::cur);

		// Считываем данные из файла
		message_file >> message2;
		std::cout << message2 << std::endl;

	}
	else
	{
		std::cout << "Could not open file messages.txt!" << std::endl;
		return 0;
	}

}