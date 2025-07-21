# ntwrkchk



Этапы работы:
синий - старт парсера данных с opi zero 3
1. красный - устройство не загрузилось, желтый - есть ошибки, зелёный - загрузилсоь
2. красный - wifi не запущен, желтый - интерфейс существует, но по различныи причина не поднят, зелёный - подключен, интерфейс поднят
3. красный - туннель не поднят, желтый - интерфейс существует, но по различныи причина не поднят, зелёный - туннель поднят
4. красный - нет активного ssh соединения, желтый ктот-то пытается подключиться и ввел не верный пароль либо не верное имя, зелёный - подключился
5. красный - интерфейс(eth0) не поднят, желтое - есть ошибки(10half/full, 100half), зелное подключен(100/1000-full duplex) 100 Мбит





Подключение светодиода
```text
Красный - 10
Зелёный - 8
Синий - 3
```





Куда что подключать
![Куда что подключать](https://raw.githubusercontent.com/azvname/ntwrkchk/5d84e765c012de4e2d8b895e4b252455e70d8f77/pinout.jpg)



Установите зависимости
```sh
sudo apt install gcc g++ git ifupdown
git clone https://github.com/orangepi-xunlong/wiringOP.git
cd wiringOP
sudo ./build clean
sudo ./build
cd

```



Клонируем репозиторий и компилируем
```sh
git clone https://github.com/azvname/ntwrkchk.git
cd ntwrkchk
gcc main.c -lwiringPi -o v4

```
Отредактируйте файл сервиса l2tp_up.serivce: укажите свой путь в ExecStart. 

Активируем сервис и добавляем в автозагрузку
```sh
sudo mv l2tp_up.service /etc/systemd/system
sudo systemctl enable --now l2tp_up.service
```


Перезагрузите устройство
