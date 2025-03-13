— — — Моя среда — — — 
У меня код работал в:
1) Visual Studion 2022 (143v)
2) Configuration Type: Application (.exe)
3) SDK 10.0 (latest installed version)
4) C++ Language Standard: C++ 17
5) C Language Standard: Default (Legacy MSVC)


— — — Установка пакетов — — —
Для установки раличных библиотек я использую vcpkg (https://vcpkg.io/en/index.html)
Для работы с ТГ ботами на С++ установил пакеты:
1) vcpkg intstall tgbot-cpp
2) vcpkg intstall  tgbot-cpp:x64-windows
<< https://vcpkg.io/en/package/tgbot-cpp 

Вот официальная документация: https://github.com/reo7sp/tgbot-cpp


— — — Ошибка — — —
При создании обычного шаблона (из документации) у меня возникла следующая ошибка:
error: building boost-headers:x64-windows failed with: BUILD_FAILED 

Или полное название ошибки: Severity	Code	Description	Project	File	Line Suppression State	Details
Error (active)	E0020	identifier "__builtin_FUNCSIG" is undefined TgBotStructure C:\vcpkg\installed\x64-windows\include\boost\asio\detail\throw_error.hpp	39		

Решение нашел на Stack Overflow от пользователя RetiredNinja. Огромное ему спасибо!
(https://stackoverflow.com/questions/78594552/builtin-funcsig-is-undefined-error-when-integrating-boost-with-visual-studio)
Необходимо перед подключением библиотек использовать макро-определение:
#define BOOST_DISABLE_CURRENT_LOCATION  

Ошибка устранена!


— — — Работа с БД — — —
Для работы с БД я использую SQLite, т.к он отлично подходить для небольших проектов.
Если проект большой можно использовать MySQL.

Чтобы установить такаже используем vcpkg:
vcpkg intstall sqlitecpp
<< https://vcpkg.io/en/package/sqlitecpp

Чтобы библиотека работала без ошибок, я использую макро-определение:
#define SQLITECPP_COMPILE_DLL

Для того чтобы открывать файлы формата .db я использую DB.Browser.for.SQLite-v3.13.1-win64.
