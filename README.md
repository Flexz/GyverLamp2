# GyverLamp2
![Logo](/docs/banner2.png)

## Особенности beta версии
- Пока что не реализован только рассвет, всё остальное работает

## Отличия от первой версии GyverLamp:
- Возможность объединять устройства в группы с синхронизированными эффектами и их автоматическим переключением
- Возможность создать свой список режимов для каждой группы устройств
- Конструктор режимов, позволяющий получить несколько сотен уникальных эффектов
- Минимум настроек в прошивке, всё настраивается из приложения
- Гибкие настройки сети, позволяющие на лету менять точки подключения, адресацию и роли
- Светомузыка - реакция на звук может быть наложена на любой эффект несколькими способами
- Адаптивная яркость благодаря датчику освещённости
- Режим работы по расписанию и таймер выключения для группы устройств
- Мультиязычное приложение со встроенными инструкциями и подсказками
- Простая и удобная загрузка прошивки (скомпилированный файл), прошивка возможна даже со смартфона!
- Обновление прошивки «по воздуху» из приложения (требуется подключение к Интернет)
- Схема как у первой версии, перепаивать электронику не нужно (без учёта микрофона и датчика освещённости)
- Автоматическое определение типа кнопки
- Устройство может работать без кнопки, все важные настройки можно сделать с приложения

Сеть:
- Работа в локальной сети роутера (все устройства подключаются к роутеру)
- Работа в локальной сети одной лампы (все устройства подключаются к одной лампе)

Время:
- Устройства подключаются к Интернету через роутер и запрашивают текущее время
- Работа по расписанию: час включения и час выключения
- Таймер выключения
- Будильник-рассвет на каждый день недели

Тип устройства:
- GyverLamp2 может работать как с лентами, так и с матрицами различной конструкции

Адресация:
- Объединение устройств в группы с индивидуальным набором настроек и режимов
- Роли Master и Slave: состояние и яркость Slave устройств подчиняется Master устройству при ручном управлении

Режимы:
- Каждой группе может быть задан свой набор режимов работы
- Режим представляет собой эффект и его настройки (сам эффект, реакция на звук, яркость, скорость и т.д.)
- Ручное переключение режимов кнопкой или из приложения (для всех устройств в группе)
- Автоматическое по порядку с установленным периодом (для всех устройств в группе)
- Автоматическое в случайном порядке с установленным периодом (для всех устройств в группе)
- Режимы синхронизированы: все устройства группы показывают один и тот же режим в любой момент времени

Эффекты:
- 7 базовых эффектов, у каждого есть индивидуальные настройки
- У некоторых эффектов возможен выбор цветовой палитры из 25 доступных
- Эффекты синхронизированы у всех устройств в группе

Реакция на звук:
- При подключении микрофона все режимы могут работать как светомузыка
- Реакция на общую громкость, отдельно низкие и отдельно высокие частоты
- Реакция на звук может менять яркость режима, а также некоторые настройки эффекта

Автоматическая яркость:
- Есть возможность подключить датчик освещённости для автоматической настройки яркости лампы

Будильник-рассвет:
- Подключенная к роутеру группа может будить в установленное время плавным рассветом
- Можно настроить время конкретные дни недели, а также яркость рассвета