#include "GForm.h" // Переконайтеся, що назва вашої форми тут правильна

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Створення та запуск вашої форми
    // OP26Lab5Graphics - це назва namespace з вашого файлу GForm.h
    // GForm - це назва класу форми
    OP26Lab5Graphics::GForm form;
    Application::Run(% form);

    return 0;
}