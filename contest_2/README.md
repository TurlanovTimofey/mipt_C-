1) Сборка и запуск из папки "..\contest_2":  
g++ -std=c++17 cpp/*.cpp -I hpp -o flot.exe  
.\flot.exe  
1) Сборка и запуск:
cd ..  
g++ -std=c++17 cpp/*.cpp -I hpp -o flot.exe  
.\flot.exe  
Далее программа ждёт ввод.
2) Схема наследования:
  2.1) База - IInventoryItem(абстрактный);
  От него 2 класса:
    ITransport(абстрактный) - добавляет score транспорту;
    IThing(абстрактный) - класс для вещей.
  Ещё независимых класс:
    IEnergyConsumer - суперспособность владения энергией (уходим от проблемы наследования ромба).
  2.2) Остальные классы наследуются от базовых:
    Helmet от IThing;
    Bike от ITransport;
    Dock от IThing и IEnergyConsumer (множественное наследование);
    ElectricBike от ITransport и IEnergyConsumer (множественное наследование);
    Scooter от ITransport и IEnergyConsumer (множественное наследование).
3) Используем умные указатели:
  3.1) unique_ptr — в main.cpp при создании новых объектов через add (только он владеет объектом в момент прохождения техосмотра). После проверки - unique_ptr и владение передаётся в парк.
  3.2) shared_ptr —  в классе Park храним парк через него для совместной работы с weak_ptr, а также в классе ModelSpec, чтобы несколько одинаковых объектов могли ссылаться на один и тот    же объект (экономим память).
  3.3) weak_ptr — используем в Fleet для "витрины" - focus_. Он не владеет объектом, а только наблюдает за ним. Если объект удаляют из парка, weak_ptr становится expired(), и show_focus выводит removed or expired.
4) catch только в main, чтобы не портить состояние парка.
  Типы исключений:
  4.1) Broken (наследник ParkError) - бросается в ServiceCenter::IfBroken, когда техосмотр отклоняет устройство;
  5.1) CommandError (наследник ParkError) - бросается в конструкторах классов, в методах Park и в main при считывании операций при: неверных аргументах, пустом id, дубликатах, при безуспешной попытке найти на "витрине", а также при неизвестной команде.
5) Шаблонный класс Registry в Registry.hpp для журнала, который хранит успешно добаленные объекты(их id). Используется в классе Park.
6) Креативная часть:
  6.1) Класс электовелосипедов (ElectricBike), который потреблет энергию. Для него добавлена команда add ebike.
  6.2) В Park добавлен метод  GetCreateSpec, с помощью которого несколько объектов могут использовать один ModelSpec.
  6.3) Подсчёт энергии в Park через dynamic_cast по IEnergyConsumer, чтобы сразу пропускать неэлектрические типы.
   
8) Список команд:
add scooter <id> <name> <energy> <score>	- Добавить электросамокат
add bike <id> <name> <score>	            - Добавить обычный велосипед
add ebike <id> <name> <energy> <score>	  - Добавить электровелосипед (креативная часть)
add helmet <id> <name>	                  - Добавить шлем
add dock <id> <name> <energy>             -	Добавить док-станцию (вещь, потребляет энергию)
energy	                                  - Напечатать суммарную суточную энергию парка (double)
novice	                                  - Список техники для новичков (имя + id), у которой score >= 6
list	                                    - Все позиции баланса
focus <id>                                -	Поставить единицу техники на «витрину»
show_focus	                              - Напечатать текущую витрину
remove <id>                             	- Убрать позицию из парка
quit	                                    - Выход из программы
9) Премер использования.
Ввод:
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add ebike E-1 Turbo 5.0 7
add helmet H-1 Pro
add dock D-1 Hub 10.0
add scooter S-2 brokenX 1.0 9
list
novice
energy
focus S-1
show_focus
remove S-1
show_focus
energy
quit

Вывод:
error: inspection rejected: brokenX
B-1 City
D-1 Hub
E-1 Turbo
H-1 Pro
S-1 ModelX
S-1 ModelX
E-1 Turbo
17.5
S-1 ModelX
removed or expired
15.0

9) Использовал ИИ, чтобы понять зачем нужны .hpp, как настроить зависимости в плюсах, объеденить и запустить все файлы в одной сборке(никогда с этим не работал).

